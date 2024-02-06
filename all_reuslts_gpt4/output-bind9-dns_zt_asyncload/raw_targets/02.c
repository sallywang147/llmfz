#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dns.h"

// Define the function type
typedef void (*func_type)(int, void*);

// Define a dummy function for loaddone
void dummyFunc(int status, void* arg) {
  // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the dns library
  dns_init(NULL, 0);

  // Create a new zone table
  struct dns_zt* zt = dns_zt_new();
  if (zt == NULL) {
    return 0;
  }

  // Consume data to get the parameters
  bool newonly = stream.ConsumeBool();
  std::string arg = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  dns_zt_asyncload(zt, newonly, dummyFunc, const_cast<char*>(arg.c_str()));

  // Clean up
  dns_zt_free(zt);

  return 0;
}