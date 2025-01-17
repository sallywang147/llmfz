#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "LzmaEnc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize LZMA encoder
  CLzmaEncProps props;
  LzmaEncProps_Init(&props);

  // Allocate memory for the encoder
  ISzAlloc alloc;
  alloc.Alloc = SzAlloc;
  alloc.Free = SzFree;

  // Initialize encoder
  CLzmaEncHandle enc = LzmaEnc_Create(&alloc);
  if (enc == 0) {
    return 0;
  }

  // Set encoder properties
  if (LzmaEnc_SetProps(enc, &props) != SZ_OK) {
    LzmaEnc_Destroy(enc, &alloc, &alloc);
    return 0;
  }

  // Prepare source data
  size_t srcLen = provider.ConsumeIntegralInRange<size_t>(0, provider.remaining_bytes());
  auto src = provider.ConsumeBytes<char>(srcLen);
  char* srcPtr = src.data();

  // Prepare destination data
  size_t destLen = srcLen * 2;  // Worst case for LZMA compression
  std::vector<char> dest(destLen);
  char* destPtr = dest.data();

  // Prepare parameters
  int writeEndMark = provider.ConsumeBool() ? 1 : 0;
  ICompressProgress progress = {0};

  // Call the function to fuzz
  LzmaEnc_MemEncode(enc, destPtr, &destLen, srcPtr, srcLen, writeEndMark, &progress, &alloc, &alloc);

  // Cleanup
  LzmaEnc_Destroy(enc, &alloc, &alloc);

  return 0;
}