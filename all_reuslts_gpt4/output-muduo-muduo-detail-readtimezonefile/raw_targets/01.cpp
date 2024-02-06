#include <fuzzer/FuzzedDataProvider.h>
#include "muduo/base/TimeZone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Extract to user defined object
  muduo::TimeZone::Data obj;
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  muduo::detail::readTimeZoneFile(ptr, &obj);
  return 0;
}