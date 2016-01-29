Audio audio;

auto Audio::coprocessor_enable(bool state) -> void {
  coprocessor = state;
  dspaudio.clear();

  dsp_rdoffset = cop_rdoffset = 0;
  dsp_wroffset = cop_wroffset = 0;
  dsp_length = cop_length = 0;
}

auto Audio::coprocessor_frequency(double input_frequency) -> void {
  dspaudio.setFrequency(input_frequency);
  dspaudio.setResampler(nall::DSP::ResampleEngine::Sinc);
  dspaudio.setResamplerFrequency(system.apuFrequency() / 768.0);
}

auto Audio::sample(int16 lsample, int16 rsample) -> void {
  if(coprocessor == false) return interface->audioSample(lsample, rsample);

  dsp_buffer[dsp_wroffset] = ((uint16)lsample << 0) + ((uint16)rsample << 16);
  dsp_wroffset = (dsp_wroffset + 1) & buffer_mask;
  dsp_length = (dsp_length + 1) & buffer_mask;
  flush();
}

auto Audio::coprocessor_sample(int16 lsample, int16 rsample) -> void {
  int samples[] = {lsample, rsample};
  dspaudio.sample(samples);
  while(dspaudio.pending()) {
    dspaudio.read(samples);

    cop_buffer[cop_wroffset] = ((uint16)samples[0] << 0) + ((uint16)samples[1] << 16);
    cop_wroffset = (cop_wroffset + 1) & buffer_mask;
    cop_length = (cop_length + 1) & buffer_mask;
    flush();
  }
}

auto Audio::flush() -> void {
  while(dsp_length > 0 && cop_length > 0) {
    uint32 dsp_sample = dsp_buffer[dsp_rdoffset];
    uint32 cop_sample = cop_buffer[cop_rdoffset];

    dsp_rdoffset = (dsp_rdoffset + 1) & buffer_mask;
    cop_rdoffset = (cop_rdoffset + 1) & buffer_mask;

    dsp_length--;
    cop_length--;

    int dsp_left  = (int16)(dsp_sample >>  0);
    int dsp_right = (int16)(dsp_sample >> 16);

    int cop_left  = (int16)(cop_sample >>  0);
    int cop_right = (int16)(cop_sample >> 16);

    interface->audioSample(
      sclamp<16>(dsp_left  + cop_left ),
      sclamp<16>(dsp_right + cop_right)
    );
  }
}
