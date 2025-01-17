#include "rawspeed/ArwDecoder.h"
#include "rawspeed/Buffer.h"
#include "rawspeed/DataBuffer.h"
#include "rawspeed/Endianness.h"
#include "rawspeed/RawImage.h"
#include "rawspeed/RawspeedException.h"
#include <cassert>
#include <cstdint>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  assert(Data);

  try {
    const rawspeed::Buffer b(Data, rawspeed::implicit_cast<rawspeed::Buffer::size_type>(Size));
    const rawspeed::DataBuffer db(b, rawspeed::Endianness::little);
    rawspeed::ArwDecoder dec;
    rawspeed::RawImage img;

    dec.decodeSRF(&img, &dec);
  } catch (const rawspeed::RawspeedException &) {
    return 0;
  }

  __builtin_unreachable();
}