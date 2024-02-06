#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "muduo/base/FileUtil.h"
#include "muduo/base/TimeZone.h"

bool muduo::detail::readTimeZoneFile(const char *file_name, muduo::TimeZone::Data *tz_data) {
  if (file_name == nullptr || tz_data == nullptr) {
    return false;
  }

  std::string content;
  if (!muduo::FileUtil::readFile(file_name, &content)) {
    return false;
  }

  return muduo::TimeZone::parseTimeZoneFile(content.c_str(), tz_data);
}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  muduo::TimeZone::Data tz_data;
  bool result = muduo::detail::readTimeZoneFile(new_str, &tz_data);
  free(new_str);
  return result;
}