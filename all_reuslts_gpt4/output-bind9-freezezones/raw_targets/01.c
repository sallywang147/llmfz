#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "dns.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dns_zone zone;
  // Initialize the dns_zone structure with random data.
  size_t consumed = stream.ConsumeData(&zone, sizeof(zone));
  if (consumed != sizeof(zone)) {
    // If we didn't have enough data to populate the structure, return early.
    return 0;
  }

  // Generate a random string for the second parameter.
  std::string uap = stream.ConsumeRemainingBytesAsString();

  // Call the function under test.
  int result = freezezones(&zone, const_cast<char*>(uap.c_str()));

  return 0;
}