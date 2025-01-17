#include <fuzzer/FuzzedDataProvider.h>
#include <fdk-aac/aacenc_lib.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  AACENCODER *hAacEncoder;
  if (aacEncOpen(&hAacEncoder, 0, 2) != AACENC_OK) {
    return 0;
  }

  AACENC_BufDesc inBufDesc;
  AACENC_BufDesc outBufDesc;
  AACENC_InArgs inargs;
  QMF_SCALE_FACTOR outargs;

  // Fill inBufDesc
  inBufDesc.numBufs = stream.ConsumeIntegralInRange<int>(1, 10);
  inBufDesc.bufs = (void **) malloc(sizeof(void *) * inBufDesc.numBufs);
  inBufDesc.bufferIdentifiers = (int *) malloc(sizeof(int) * inBufDesc.numBufs);
  inBufDesc.bufSizes = (int *) malloc(sizeof(int) * inBufDesc.numBufs);
  inBufDesc.bufElSizes = (int *) malloc(sizeof(int) * inBufDesc.numBufs);

  for (int i = 0; i < inBufDesc.numBufs; ++i) {
    inBufDesc.bufferIdentifiers[i] = stream.ConsumeIntegral<int>();
    inBufDesc.bufSizes[i] = stream.ConsumeIntegral<int>();
    inBufDesc.bufElSizes[i] = stream.ConsumeIntegral<int>();
    inBufDesc.bufs[i] = malloc(inBufDesc.bufSizes[i] * inBufDesc.bufElSizes[i]);
  }

  // Fill outBufDesc
  outBufDesc.numBufs = stream.ConsumeIntegralInRange<int>(1, 10);
  outBufDesc.bufs = (void **) malloc(sizeof(void *) * outBufDesc.numBufs);
  outBufDesc.bufferIdentifiers = (int *) malloc(sizeof(int) * outBufDesc.numBufs);
  outBufDesc.bufSizes = (int *) malloc(sizeof(int) * outBufDesc.numBufs);
  outBufDesc.bufElSizes = (int *) malloc(sizeof(int) * outBufDesc.numBufs);

  for (int i = 0; i < outBufDesc.numBufs; ++i) {
    outBufDesc.bufferIdentifiers[i] = stream.ConsumeIntegral<int>();
    outBufDesc.bufSizes[i] = stream.ConsumeIntegral<int>();
    outBufDesc.bufElSizes[i] = stream.ConsumeIntegral<int>();
    outBufDesc.bufs[i] = malloc(outBufDesc.bufSizes[i] * outBufDesc.bufElSizes[i]);
  }

  // Fill inargs
  inargs.numInSamples = stream.ConsumeIntegral<int>();
  inargs.numAncBytes = stream.ConsumeIntegral<int>();

  // Fill outargs
  outargs.scale = stream.ConsumeIntegral<int>();

  // Call the function
  aacEncEncode(hAacEncoder, &inBufDesc, &outBufDesc, &inargs, &outargs);

  // Free memory
  for (int i = 0; i < inBufDesc.numBufs; ++i) {
    free(inBufDesc.bufs[i]);
  }
  free(inBufDesc.bufs);
  free(inBufDesc.bufferIdentifiers);
  free(inBufDesc.bufSizes);
  free(inBufDesc.bufElSizes);

  for (int i = 0; i < outBufDesc.numBufs; ++i) {
    free(outBufDesc.bufs[i]);
  }
  free(outBufDesc.bufs);
  free(outBufDesc.bufferIdentifiers);
  free(outBufDesc.bufSizes);
  free(outBufDesc.bufElSizes);

  aacEncClose(&hAacEncoder);

  return 0;
}