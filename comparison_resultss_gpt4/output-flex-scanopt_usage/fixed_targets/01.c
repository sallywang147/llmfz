#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "scanopt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file for writing
  FILE *fp = tmpfile();
  if (fp == nullptr) {
    return 0;
  }

  scanopt_t scanner;
  std::string usage = stream.ConsumeRandomLengthString();

  // Call the function to fuzz
  scanopt_usage(&scanner, fp, usage.c_str());

  // Close the temporary file
  fclose(fp);

  return 0;
}