#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "jsoncons/json.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  jsoncons::json j1, j2;

  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRandomLengthString();

  try {
    j1 = jsoncons::json::parse(str1);
  } catch (jsoncons::json_exception&) {
    // Ignore parse errors.
  }

  try {
    j2 = jsoncons::json::parse(str2);
  } catch (jsoncons::json_exception&) {
    // Ignore parse errors.
  }

  j1.move_assignment(&j2);

  return 0;
}