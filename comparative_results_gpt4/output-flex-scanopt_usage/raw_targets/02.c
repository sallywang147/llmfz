#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "scanopt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize scanner
  scanopt_t* scanner = scanopt_init(NULL, 0, NULL);
  if (!scanner) {
    return 0;
  }

  // Initialize file pointer
  FILE* fp = tmpfile();
  if (!fp) {
    scanopt_destroy(scanner);
    return 0;
  }

  // Consume data for usage string
  std::string usage = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  scanopt_usage(scanner, fp, usage.c_str());

  // Clean up
  fclose(fp);
  scanopt_destroy(scanner);

  return 0;
}