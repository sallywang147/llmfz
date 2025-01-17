#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "aacenc_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  AACENC_BufDesc inBufDesc;
  inBufDesc.numBufs = 1;
  inBufDesc.bufs = &stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size)).data();
  inBufDesc.bufSizes = &stream.ConsumeIntegralInRange(0, size);

  AACENC_BufDesc outBufDesc;
  outBufDesc.numBufs = 1;
  outBufDesc.bufs = &stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size)).data();
  outBufDesc.bufSizes = &stream.ConsumeIntegralInRange(0, size);

  AACENC_InArgs inargs;
  inargs.numInSamples = stream.ConsumeIntegral<uint32_t>();
  inargs.prevInq = stream.ConsumeIntegral<uint32_t>();
  inargs.prevOutQ = stream.ConsumeIntegral<uint32_t>();

  QMF_SCALE_FACTOR outargs;
  outargs.num_sfb = stream.ConsumeIntegral<uint32_t>();
  outargs.scalefactor = &stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size)).data();

  AACENCODER* hAacEncoder = aacEncOpen(stream.ConsumeIntegral<uint32_t>(), stream.ConsumeIntegral<uint32_t>(), stream.ConsumeIntegral<uint32_t>());
  if (hAacEncoder == nullptr) {
    return 0;
  }

  int ret = aacEncEncode(hAacEncoder, &inBufDesc, &outBufDesc, &inargs, &outargs);
  if (ret != AACENC_OK) {
    return 0;
  }

  aacEncClose(hAacEncoder);
  return 0;
}