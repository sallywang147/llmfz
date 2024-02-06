#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>

#include "pistache/http.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  std::ostringstream stream;
  std::ostream* ostream_ptr = &stream;

  Pistache::Http::Cookie cookie;
  cookie.name = fuzzed_data.ConsumeRandomLengthString();
  cookie.value = fuzzed_data.ConsumeRandomLengthString();
  cookie.expires = fuzzed_data.ConsumeIntegral<unsigned long>();
  cookie.maxAge = fuzzed_data.ConsumeIntegral<unsigned long>();
  cookie.domain = fuzzed_data.ConsumeRandomLengthString();
  cookie.path = fuzzed_data.ConsumeRandomLengthString();
  cookie.secure = fuzzed_data.ConsumeBool();
  cookie.httpOnly = fuzzed_data.ConsumeBool();

  Pistache::Http::operator<<(ostream_ptr, &cookie);

  return 0;
}