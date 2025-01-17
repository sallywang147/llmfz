#include <cstdint>
#include <cstdio>

#include "codes/PrefixCodeDecoder.h"
#include "codes/PrefixCodeDecoder/Common.h"
#include "codes/PrefixCodeLUTDecoder.h"
#include "codes/PrefixCodeLookupDecoder.h"
#include "codes/PrefixCodeTreeDecoder.h"
#include "codes/PrefixCodeVectorDecoder.h"
#include "io/BitPumpJPEG.h"
#include "io/BitPumpMSB.h"
#include "io/BitPumpMSB32.h"
#include "io/Buffer.h"
#include "io/ByteStream.h"
#include "io/Endianness.h"
#include "io/IOException.h"
#include "rawspeed/RawspeedException.h"
#include "rawspeed/VC5Decompressor.h"
#include "rawspeed/VC5Decompressor/VC5Decompressor.h"

namespace rawspeed {

struct VC5CodeTag;

} // namespace rawspeed

namespace {

template <typename Pump, bool IsFullDecode, typename HT0, typename HT1> void workloop(rawspeed::ByteStream bs0, rawspeed::ByteStream bs1, const HT0 &ht0, const HT1 &ht1) {
  Pump bits0(bs0.peekRemainingBuffer());
  Pump bits1(bs1.peekRemainingBuffer());

  while (true) {
    int decoded0;
    int decoded1;

    bool failure0 = false;
    bool failure1 = false;

    try {
      decoded1 = ht1.template decode<decltype(bits1), IsFullDecode>(bits1);
    } catch (const rawspeed::IOException &) {
      // For now, let's ignore stream depleteon issues.
      throw;
    } catch (const rawspeed::RawspeedException &) {
      failure1 = true;
    }

    try {
      decoded0 = ht0.template decode<decltype(bits0), IsFullDecode>(bits0);
    } catch (const rawspeed::IOException &) {
      // For now, let's ignore stream depleteon issues.
      throw;
    } catch (const rawspeed::RawspeedException &) {
      failure0 = true;
    }

    // They both should either fail or succeed, else there is a bug.
    assert(failure0 == failure1);

    // If any failed, we can't continue.
    if (failure0 || failure1)
      ThrowRSE("Failure detected");

    (void)decoded0;
    (void)decoded1;

    // They both should have decoded the same value.
    assert(decoded0 == decoded1);
  }
}

template <typename Pump, typename HT0, typename HT1> void checkPump(rawspeed::ByteStream bs0, rawspeed::ByteStream bs1, const HT0 &ht0, const HT1 &ht1) {
  assert(bs0.getPosition() == bs1.getPosition());
  assert(ht0.isFullDecode() == ht1.isFullDecode());
  if (ht0.isFullDecode())
    workloop<Pump, /*IsFullDecode=*/true>(bs0, bs1, ht0, ht1);
  else
    workloop<Pump, /*IsFullDecode=*/false>(bs0, bs1, ht0, ht1);
}

template <typename CodeTag> void checkFlavour(rawspeed::ByteStream bs) {
  rawspeed::ByteStream bs0 = bs;
  rawspeed::ByteStream bs1 = bs;

  const auto ht0 = createPrefixCodeDecoder<rawspeed::IMPL0<CodeTag>>(bs0);
  const auto ht1 = createPrefixCodeDecoder<rawspeed::IMPL1<CodeTag>>(bs1);

  // should have consumed 16 bytes for n-codes-per-length, at *least* 1 byte
  // as code value, and a byte per 'fixDNGBug16'/'fullDecode' booleans
  assert(bs0.getPosition() == bs1.getPosition());

  // Which bit pump should we use?
  bs1.skipBytes(1);
  switch (bs0.getByte()) {
  case 0:
    checkPump<rawspeed::BitPumpMSB>(bs0, bs1, ht0, ht1);
    break;
  case 1:
    checkPump<rawspeed::BitPumpMSB32>(bs0, bs1, ht0, ht1);
    break;
  case 2:
    checkPump<rawspeed::BitPumpJPEG>(bs0, bs1, ht0, ht1);
    break;
  default:
    ThrowRSE("Unknown bit pump");
  }
}

} // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  assert(Data);

  try {
    const rawspeed::Buffer b(Data, rawspeed::implicit_cast<rawspeed::Buffer::size_type>(Size));
    const rawspeed::DataBuffer db(b, rawspeed::Endianness::little);
    rawspeed::ByteStream bs(db);

    // Which flavor?
    switch (bs.getByte()) {
    case 0:
      checkFlavour<rawspeed::VC5CodeTag>(bs);
      break;
    default:
      ThrowRSE("Unknown flavor");
    }

    rawspeed::VC5Decompressor d;
    d.combineFinalLowpassBands(&d);
  } catch (const rawspeed::RawspeedException &) {
    return 0;
  }

  __builtin_unreachable();
}