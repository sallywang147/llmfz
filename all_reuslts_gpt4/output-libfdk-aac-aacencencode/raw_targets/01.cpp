#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "aacenc_lib.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 10) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  AACENCODER* hAacEncoder = nullptr;
  AACENC_BufDesc inBufDesc;
  AACENC_BufDesc outBufDesc;
  AACENC_InArgs inargs;
  QMF_SCALE_FACTOR outargs;

  // Initialize AAC encoder
  if (aacEncOpen(&hAacEncoder, 0, 2) != AACENC_OK) {
    return 0;
  }

  // Initialize input and output buffer descriptors
  inBufDesc.numBufs = 1;
  inBufDesc.bufs = (void**)&data;
  inBufDesc.bufferIdentifiers = (int*)stream.ConsumeIntegral<int>();
  inBufDesc.bufSizes = (int*)stream.ConsumeIntegral<int>();
  inBufDesc.bufElSizes = (int*)stream.ConsumeIntegral<int>();

  outBufDesc.numBufs = 1;
  outBufDesc.bufs = (void**)&data;
  outBufDesc.bufferIdentifiers = (int*)stream.ConsumeIntegral<int>();
  outBufDesc.bufSizes = (int*)stream.ConsumeIntegral<int>();
  outBufDesc.bufElSizes = (int*)stream.ConsumeIntegral<int>();

  // Initialize input arguments
  inargs.numInSamples = stream.ConsumeIntegral<int>();
  inargs.numAncBytes = stream.ConsumeIntegral<int>();

  // Initialize output arguments
  outargs.scale = stream.ConsumeIntegral<int>();
  outargs.scale_bits = stream.ConsumeIntegral<int>();

  // Call the target function
  aacEncEncode(hAacEncoder, &inBufDesc, &outBufDesc, &inargs, &outargs);

  // Close the AAC encoder
  aacEncClose(&hAacEncoder);

  return 0;
}