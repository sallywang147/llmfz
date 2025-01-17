#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "dns.h"

// Define a callback function that matches the func_type signature
void callback_func(char *arg) {
  // Do nothing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Create a FuzzedDataProvider instance
  FuzzedDataProvider provider(data, size);

  // Create and initialize a dns_view object
  struct dns_view *view = dns_view_new();
  if (!view) {
    return 0;
  }

  // Consume data from the provider
  bool newonly = provider.ConsumeBool();
  std::string arg = provider.ConsumeRandomLengthString();

  // Call the function under test
  int result = dns_view_asyncload(view, newonly, callback_func, const_cast<char*>(arg.c_str()));

  // Cleanup
  dns_view_delete(view);

  return 0;
}