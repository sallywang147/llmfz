#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>

#include "pistache/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string cookieName = stream.ConsumeRandomLengthString();
  std::string cookieValue = stream.ConsumeRandomLengthString();

  Pistache::Http::Cookie cookie(cookieName, cookieValue);

  std::ostringstream oss;
  cookie.write(&cookie, &oss);

  return 0;
}