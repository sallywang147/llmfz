#include "RawImage.h"
#include "NakedDecoder.h"
#include "codes/PrefixCodeDecoder.h"
#include "codes/PrefixCodeLUTDecoder.h"
#include "codes/PrefixCodeTreeDecoder.h"
#include "codes/PrefixCodeVectorDecoder.h"
#include "io/ByteStream.h"
#include "io/Endianness.h"
#include <cassert>
#include <cstdio>

namespace rawspeed {
struct BaselineCodeTag;
struct VC5CodeTag;
} // namespace rawspeed

namespace {

template <typename Pump, bool IsFullDecode, typename HT0, typename HT1> void workloop(RawImage &rawImage, NakedDecoder &nakedDecoder, ByteStream bs0, ByteStream bs1, const HT0 &ht0, const HT1 &ht1) {
  Pump bits0(bs0.peekRemainingBuffer());
  Pump bits1(bs1.peekRemainingBuffer());

  while (true) {
    int decoded0;
    int decoded1;

    bool failure0 = false;
    bool failure1 = false;

    try {
      decoded1 = ht1.template decode<decltype(bits1), IsFullDecode>(bits1);
    } catch (const IOException &) {
      // For now, let's ignore stream depleteon issues.
      throw;
    } catch (const RawspeedException &) {
      failure1 = true;
    }

    try {
      decoded0 = ht0.template decode<decltype(bits0), IsFullDecode>(bits0);
    } catch (const IOException &) {
      // For now, let's ignore stream depleteon issues.
      throw;
    } catch (const RawspeedException &) {
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

template <typename Pump, typename HT0, typename HT1> void checkPump(RawImage &rawImage, NakedDecoder &nakedDecoder, ByteStream bs0, ByteStream bs1, const HT0 &ht0, const HT1 &ht1) {
  assert(bs0.getPosition() == bs1.getPosition());
  assert(ht0.isFullDecode() == ht1.isFullDecode());
  if (ht0.isFullDecode())
    workloop<Pump, /*IsFullDecode=*/true>(rawImage, nakedDecoder, bs0, bs1, ht0, ht1);
  else
    workloop<Pump, /*IsFullDecode=*/false>(rawImage, nakedDecoder, bs0, bs1, ht0, ht1);
}

template <typename CodeTag> void checkFlavour(RawImage &rawImage, NakedDecoder &nakedDecoder, ByteStream bs) {
  ByteStream bs0 = bs;
  ByteStream bs1 = bs;

#ifndef BACKIMPL0
  const auto ht0 = createPrefixCodeDecoder<IMPL0<CodeTag>>(bs0);
#else
  const auto ht0 = createPrefixCodeDecoder<IMPL0<CodeTag, BACKIMPL0<CodeTag>>>(bs0);
#endif

#ifndef BACKIMPL1
  const auto ht1 = createPrefixCodeDecoder<IMPL1<CodeTag>>(bs1);
#else
  const auto ht1 = createPrefixCodeDecoder<IMPL1<CodeTag, BACKIMPL1<CodeTag>>>(bs1);
#endif

  // should have consumed 16 bytes for n-codes-per-length, at *least* 1 byte
  // as code value, and a byte per 'fixDNGBug16'/'fullDecode' booleans
  assert(bs0.getPosition() == bs1.getPosition());

  // Which bit pump should we use?
  bs1.skipBytes(1);
  switch (bs0.getByte()) {
  case 0:
    checkPump<BitPumpMSB>(rawImage, nakedDecoder, bs0, bs1, ht0, ht1);
    break;
  case 1:
    checkPump<BitPumpMSB32>(rawImage, nakedDecoder, bs0, bs1, ht0, ht1);
    break;
  case 2:
    checkPump<BitPumpJPEG>(rawImage, nakedDecoder, bs0, bs1, ht0, ht1);
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
    const Buffer b(Data, implicit_cast<Buffer::size_type>(Size));
    const DataBuffer db(b, Endianness::little);
    ByteStream bs(db);

    // Which flavor?
    switch (bs.getByte()) {
    case 0:
      checkFlavour<BaselineCodeTag>(RawImage(), NakedDecoder(), bs);
      break;
    case 1:
      checkFlavour<VC5CodeTag>(RawImage(), NakedDecoder(), bs);
      break;
    default:
      ThrowRSE("Unknown flavor");
    }
  } catch (const RawspeedException &) {
    return 0;
  }

  __builtin_unreachable();
}