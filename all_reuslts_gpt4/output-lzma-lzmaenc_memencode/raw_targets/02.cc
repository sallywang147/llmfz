#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "LzmaEnc.h"
#include "Alloc.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for src
  size_t srcLen = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string src = stream.ConsumeBytesAsString(srcLen);
  
  // Initialize destLen and dest
  size_t destLen = srcLen * 2; // Maximum compression ratio is 2:1
  char* dest = (char*)malloc(destLen);
  
  // Initialize pp
  char* pp = nullptr;

  // Initialize writeEndMark
  int writeEndMark = stream.ConsumeBool();

  // Initialize progress
  ICompressProgress progress;
  
  // Initialize alloc and allocBig
  ISzAlloc alloc;
  ISzAlloc allocBig;
  alloc.Alloc = SzAlloc;
  alloc.Free = SzFree;
  allocBig.Alloc = SzAlloc;
  allocBig.Free = SzFree;

  // Call the target function
  int ret = LzmaEnc_MemEncode(pp, dest, &destLen, (char*)src.data(), srcLen, writeEndMark, &progress, &alloc, &allocBig);

  // Free allocated memory
  free(dest);

  return 0;
}