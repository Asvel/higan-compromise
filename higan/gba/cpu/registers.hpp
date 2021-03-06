struct Registers {
  struct DMAControl {
    uint2 targetmode;
    uint2 sourcemode;
    uint1 repeat;
    uint1 size;
    uint1 drq;
    uint2 timingmode;
    uint1 irq;
    uint1 enable;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const DMAControl&) -> DMAControl& = delete;
  };

  struct DMA {
    varuint source;
    varuint target;
    varuint length;
    uint32 data;
    DMAControl control;

    //internal
    bool pending;
    struct Run {
      varuint target;
      varuint source;
      varuint length;
    } run;
  } dma[4];

  struct TimerControl {
    uint2 frequency;
    uint1 cascade;
    uint1 irq;
    uint1 enable;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const TimerControl&) -> TimerControl& = delete;
  };

  struct Timer {
    uint16 period;
    uint16 reload;
    bool pending;
    TimerControl control;
  } timer[4];

  struct SerialControl {
    uint1 shiftclockselect;
    uint1 shiftclockfrequency;
    uint1 transferenablereceive;
    uint1 transferenablesend;
    uint1 startbit;
    uint1 transferlength;
    uint1 irqenable;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const SerialControl&) -> SerialControl& = delete;
  };

  struct Serial {
    uint16 data[4];
    SerialControl control;
    uint8 data8;
  } serial;

  struct KeypadControl {
    uint1 flag[10];
    uint1 enable;
    uint1 condition;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const KeypadControl&) -> KeypadControl& = delete;
  };

  struct Keypad {
    KeypadControl control;
  } keypad;

  struct JoybusSettings {
    uint1 sc;
    uint1 sd;
    uint1 si;
    uint1 so;
    uint1 scmode;
    uint1 sdmode;
    uint1 simode;
    uint1 somode;
    uint1 irqenable;
    uint2 mode;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const JoybusSettings&) -> JoybusSettings& = delete;
  };

  struct JoybusControl {
    uint1 resetsignal;
    uint1 receivecomplete;
    uint1 sendcomplete;
    uint1 irqenable;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const JoybusControl&) -> JoybusControl& = delete;
  };

  struct JoybusStatus {
    uint1 receiveflag;
    uint1 sendflag;
    uint2 generalflag;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const JoybusStatus&) -> JoybusStatus& = delete;
  };

  struct Joybus {
    JoybusSettings settings;
    JoybusControl control;
    uint32 receive;
    uint32 transmit;
    JoybusStatus status;
  } joybus;

  uint1 ime;

  struct Interrupt {
    uint1 vblank;
    uint1 hblank;
    uint1 vcoincidence;
    uint1 timer[4];
    uint1 serial;
    uint1 dma[4];
    uint1 keypad;
    uint1 cartridge;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const Interrupt&) -> Interrupt& = delete;
  };

  struct IRQ {
    Interrupt enable;
    Interrupt flag;
  } irq;

  struct WaitControl {
    uint2 nwait[4];
    uint1 swait[4];
    uint2 phi;
    uint1 prefetch;
    uint1 gametype;

    operator uint16() const;
    auto operator=(uint16 source) -> uint16;
    auto operator=(const WaitControl&) -> WaitControl& = delete;
  };

  struct Wait {
    WaitControl control;
  } wait;

  struct MemoryControl {
    uint1 disable;
    uint3 unknown1;
    uint1 ewram;
    uint4 ewramwait;
    uint4 unknown2;

    operator uint32() const;
    auto operator=(uint32 source) -> uint32;
    auto operator=(const MemoryControl&) -> MemoryControl& = delete;
  };

  struct Memory {
    MemoryControl control;
  } memory;

  uint1 postboot;
  enum class Mode : uint { Normal, Halt, Stop } mode;
  uint clock;
} regs;
