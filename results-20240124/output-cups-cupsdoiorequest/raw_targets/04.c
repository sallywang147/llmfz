 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ipp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  ipp_t* request = ippNew();
  FuzzedDataProvider stream(data, size);
  const std::string resource = stream.ConsumeRemainingBytesAsString();
  cupsDoIORequest(nullptr, request, const_cast<char*>(resource.c_str()), 0, 0);
  ippDelete(request);
  return 0;
}