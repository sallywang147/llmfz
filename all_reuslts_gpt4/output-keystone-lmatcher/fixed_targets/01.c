#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "regex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  struct re_guts guts;
  guts.magic = stream.ConsumeIntegral<unsigned long>();
  guts.csetsize = stream.ConsumeIntegral<unsigned int>();
  guts.ncsets = stream.ConsumeIntegral<unsigned int>();
  guts.neol = stream.ConsumeIntegral<unsigned char>();
  guts.cflags = stream.ConsumeIntegral<unsigned long>();
  guts.iflags = stream.ConsumeIntegral<unsigned long>();
  guts.nbol = stream.ConsumeIntegral<unsigned char>();
  guts.nbol = stream.ConsumeIntegral<unsigned char>();
  guts.nsbol = stream.ConsumeIntegral<unsigned char>();
  guts.neol = stream.ConsumeIntegral<unsigned char>();
  guts.ncategories = stream.ConsumeIntegral<int>();
  guts.maxlook = stream.ConsumeIntegral<int>();
  guts.nsub = stream.ConsumeIntegral<int>();
  
  size_t str_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::string str = stream.ConsumeBytesAsString(str_size);
  char* str_ptr = const_cast<char*>(str.c_str());

  struct timespec times;
  times.tv_sec = stream.ConsumeIntegral<time_t>();
  times.tv_nsec = stream.ConsumeIntegral<long>();

  int flags = stream.ConsumeIntegral<int>();

  lmatcher(&guts, str_ptr, str_size, &times, flags);

  return 0;
}