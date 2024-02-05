#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "scanopt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize scanner
  scanopt_t* scanner = scanopt_init(NULL, 0, NULL);
  if (scanner == NULL) {
    return 0;
  }

  // Create a temporary file for writing
  FILE* fp = tmpfile();
  if (fp == NULL) {
    scanopt_destroy(scanner);
    return 0;
  }

  // Consume remaining bytes as a string
  std::string usage_str = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  scanopt_usage(scanner, fp, usage_str.c_str());

  // Cleanup
  fclose(fp);
  scanopt_destroy(scanner);

  return 0;
}