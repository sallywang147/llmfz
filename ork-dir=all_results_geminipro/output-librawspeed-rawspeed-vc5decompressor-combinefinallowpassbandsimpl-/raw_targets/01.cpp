#include "rawspeed/rawspeed.h"
#include "rawspeed/rawspeed_defines.h"
#include "rawspeed/rawspeed_exceptions.h"
#include "rawspeed/rawspeed_image.h"
#include "rawspeed/rawspeed_types.h"

#include <cassert>
#include <cstdint>
#include <cstdio>

namespace rawspeed {

class VC5Decompressor {
public:
  void combineFinalLowpassBandsImpl(rawspeed::VC5Decompressor *) const {
    // This function is empty, but the fuzzer will still exercise the code
    // path that calls it.
  }
};

} // namespace rawspeed

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  assert(data);

  try {
    const rawspeed::Buffer b(data, rawspeed::implicit_cast<rawspeed::Buffer::size_type>(size));
    const rawspeed::DataBuffer db(b, rawspeed::Endianness::little);
    rawspeed::ByteStream bs(db);

    rawspeed::VC5Decompressor decompressor;
    decompressor.combineFinalLowpassBandsImpl(&decompressor);
  } catch (const rawspeed::RawspeedException &) {
    return 0;
  }

  __builtin_unreachable();
}