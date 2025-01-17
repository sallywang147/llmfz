#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "XzUnpacker.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize XzUnpacker
  CXzUnpacker xz_unpacker;
  XzUnpacker_Construct(&xz_unpacker);

  // Prepare the source buffer
  size_t srcLen = stream.remaining_bytes();
  char* src = (char*)stream.ConsumeRemainingBytes().data();

  // Prepare the destination buffer
  size_t destLen = srcLen * 2; // Just a guess, could be adjusted
  std::vector<char> dest(destLen);

  // Prepare other parameters
  int finishMode = stream.ConsumeBool() ? CODER_FINISH_END : CODER_FINISH_ANY;
  int status;

  // Call the function to fuzz
  XzUnpacker_CodeFull(&xz_unpacker, dest.data(), &destLen, src, &srcLen, finishMode, &status);

  // Free the resources
  XzUnpacker_Free(&xz_unpacker);

  return 0;
}