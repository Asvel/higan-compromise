struct NECDSP : Processor::uPD96050, Coprocessor {
  static auto Enter() -> void;
  auto enter() -> void;

  auto read(uint addr, uint8 data) -> uint8;
  auto write(uint addr, uint8 data) -> void;

  auto readRAM(uint addr, uint8 data) -> uint8;
  auto writeRAM(uint addr, uint8 data) -> void;

  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto firmware() const -> vector<uint8>;
  auto serialize(serializer&) -> void;
};

extern NECDSP necdsp;
