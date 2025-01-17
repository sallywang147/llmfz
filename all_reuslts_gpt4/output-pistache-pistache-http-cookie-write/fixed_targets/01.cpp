#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>

#include "pistache/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new cookie
  Pistache::Http::Cookie cookie;

  // Create a new output stream
  std::ostringstream oss;

  // Call the function to fuzz
  cookie.write(&cookie, &oss);

  return 0;
}