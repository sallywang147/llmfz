#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

// Function to fuzz
extern "C" int tmp_dir(char ** ret);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *ret;

  // Call the function with the fuzzed input
  tmp_dir(&ret);

  // Free the allocated memory
  if (ret != nullptr) {
    free(ret);
  }

  return 0;
}