 #include "cups/cups.h"
#include "cups/ipp.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* resource = stream.ConsumeRandomLengthString().c_str();
  const int infile = stream.ConsumeIntegral<int>();
  const int outfile = stream.ConsumeIntegral<int>();
  ipp_t* request = ippNew();
  cupsDoIORequest(nullptr, request, const_cast<char*>(resource), infile, outfile);
  ippDelete(request);
  return 0;
}