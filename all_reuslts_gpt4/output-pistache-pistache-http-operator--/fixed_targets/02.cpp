#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>

#include "pistache/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string cookieName = stream.ConsumeRandomLengthString();
  std::string cookieValue = stream.ConsumeRandomLengthString();
  Pistache::Http::Cookie cookie(cookieName, cookieValue);

  std::ostringstream oss;
  std::ostream* os = &oss;

  os = Pistache::Http::operator<<(os, &cookie);

  return 0;
}