#include <fuzzer/FuzzedDataProvider.h>
#include "muduo/base/TimeZone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string filename = stream.ConsumeRandomLengthString();
  char *filename_ptr = filename.c_str();

  muduo::TimeZone::Data tzData;

  muduo::detail::readTimeZoneFile(filename_ptr, &tzData);

  return 0;
}