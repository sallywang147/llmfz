#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstddef>
#include <string>

#include "muduo/base/TimeZone.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRemainingBytesAsString();
  char* zonefile = const_cast<char*>(str.c_str());

  muduo::TimeZone tz;
  muduo::TimeZone::loadZoneFile(&tz, zonefile);

  return 0;
}