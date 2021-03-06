#pragma once

namespace nall {

namespace Hash {
  auto CRC16::digest() -> string {
    return hex(value(), 4L);
  }

  auto CRC32::digest() -> string {
    return hex(value(), 8L);
  }

  auto SHA256::digest() const -> string {
    string result;
    for(auto n : value()) result.append(hex(n, 2L));
    return result;
  }
}

auto crc16(rstring self) -> string {
  return Hash::CRC16(self.data(), self.size()).digest();
}

auto crc32(rstring self) -> string {
  return Hash::CRC32(self.data(), self.size()).digest();
}

auto sha256(rstring self) -> string {
  return Hash::SHA256(self.data(), self.size()).digest();
}

}
