#include <fuzzer/FuzzedDataProvider.h>
#include <pistache/http_header.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Pistache::Http::Header::Date dateHeader;
  std::ostringstream oss;

  dateHeader.write(&dateHeader, &oss);

  return 0;
}