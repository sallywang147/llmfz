#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "muduo/base/TimeZone.h"

extern "C" {
#include "muduo/base/TimeZoneFile.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  muduo::TimeZone::Data tz_data;
  bool ret = muduo::detail::readTimeZoneFile(new_str, &tz_data);
  free(new_str);
  return ret ? 0 : 1;
}