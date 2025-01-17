#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "scanopt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Create a temporary file for writing.
  FILE *fp = tmpfile();
  if (fp == NULL) {
    return 0;
  }

  // Initialize scanopt_t structure.
  scanopt_t scanner;
  scanner.optc = 0;

  // Create a usage string.
  std::string usage = provider.ConsumeRemainingBytesAsString();

  // Call the function to fuzz.
  scanopt_usage(&scanner, fp, usage.c_str());

  // Close the temporary file.
  fclose(fp);

  return 0;
}