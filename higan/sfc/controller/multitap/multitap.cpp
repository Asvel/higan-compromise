Multitap::Multitap(bool port) : Controller(port) {
  latched = 0;
  counter1 = 0;
  counter2 = 0;
}

auto Multitap::data() -> uint2 {
  if(latched) return 2;  //multitap detection
  unsigned index, port1, port2;

  if(iobit()) {
    index = counter1;
    if(index >= 16) return 3;
    counter1++;
    if(index >= 12) return 0;
    port1 = 0;  //controller 1
    port2 = 1;  //controller 2
  } else {
    index = counter2;
    if(index >= 16) return 3;
    counter2++;
    if(index >= 12) return 0;
    port1 = 2;  //controller 3
    port2 = 3;  //controller 4
  }

  bool data1 = interface->inputPoll(port, (unsigned)Device::ID::Multitap, port1 * 12 + index);
  bool data2 = interface->inputPoll(port, (unsigned)Device::ID::Multitap, port2 * 12 + index);
  return (data2 << 1) | (data1 << 0);
}

auto Multitap::latch(bool data) -> void {
  if(latched == data) return;
  latched = data;
  counter1 = 0;
  counter2 = 0;
}
