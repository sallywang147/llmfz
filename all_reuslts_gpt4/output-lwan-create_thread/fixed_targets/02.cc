#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "lwan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lwan l;
  struct lwan_thread thread;

  // Initialize the lwan structure
  lwan_init(&l);

  // Call the function to fuzz
  create_thread(&l, &thread);

  // Cleanup
  lwan_thread_shutdown(&thread);
  lwan_shutdown(&l);

  return 0;
}