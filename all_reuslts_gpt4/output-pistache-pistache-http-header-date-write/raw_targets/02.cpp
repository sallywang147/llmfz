#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <pistache/http_header.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a Date object
  Pistache::Http::Header::Date date;

  // Create a stringstream object
  std::stringstream ss;

  // Write the date to the stringstream
  date.write(&date, &ss);

  return 0;
}