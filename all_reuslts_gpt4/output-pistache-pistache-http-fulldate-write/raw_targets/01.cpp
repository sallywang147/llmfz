#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <sstream>

#include "pistache/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::__bucket_list_deallocator* bucket_list_deallocator = nullptr;
  std::ostringstream oss;
  std::ostream* ostream = &oss;
  int integer = stream.ConsumeIntegral<int>();

  Pistache::Http::FullDate fullDate;
  fullDate.write(bucket_list_deallocator, ostream, integer);

  return 0;
}