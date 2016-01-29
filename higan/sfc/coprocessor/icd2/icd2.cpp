#include <sfc/sfc.hpp>

namespace SuperFamicom {

#include "interface/interface.cpp"
#include "mmio/mmio.cpp"
#include "serialization.cpp"
ICD2 icd2;

auto ICD2::Enter() -> void { icd2.enter(); }

auto ICD2::enter() -> void {
  while(true) {
    if(scheduler.sync == Scheduler::SynchronizeMode::All) {
      GameBoy::system.runtosave();
      scheduler.exit(Scheduler::ExitReason::SynchronizeEvent);
    }

    if(r6003 & 0x80) {
      GameBoy::system.run();
      step(GameBoy::system.clocks_executed);
      GameBoy::system.clocks_executed = 0;
    } else {  //DMG halted
      audio.coprocessor_sample(0x0000, 0x0000);
      step(1);
    }
    synchronizeCPU();
  }
}

auto ICD2::init() -> void {
}

auto ICD2::load() -> void {
  bind = GameBoy::interface->bind;
  hook = GameBoy::interface->hook;
  GameBoy::interface->bind = this;
  GameBoy::interface->hook = this;
}

auto ICD2::unload() -> void {
  GameBoy::interface->bind = bind;
  GameBoy::interface->hook = hook;
}

auto ICD2::power() -> void {
  audio.coprocessor_enable(true);
  audio.coprocessor_frequency(2 * 1024 * 1024);
}

auto ICD2::reset() -> void {
  create(ICD2::Enter, cpu.frequency / 5);

  r6003 = 0x00;
  r6004 = 0xff;
  r6005 = 0xff;
  r6006 = 0xff;
  r6007 = 0xff;
  for(auto& r : r7000) r = 0x00;
  mlt_req = 0;

  for(auto& n : output) n = 0xff;
  read_bank = 0;
  read_addr = 0;
  write_bank = 0;
  write_addr = 0;

  packetsize = 0;
  joyp_id = 3;
  joyp15lock = 0;
  joyp14lock = 0;
  pulselock = true;

  GameBoy::system.init();
  GameBoy::system.power();
}

}
