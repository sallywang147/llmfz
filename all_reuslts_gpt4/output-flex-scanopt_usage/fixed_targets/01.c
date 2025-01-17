#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "scanopt.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Extract a string for the usage parameter
  std::string usage = provider.ConsumeRandomLengthString();
  
  // Initialize the scanner and fp
  char* scanner[2];
  scanner[0] = nullptr;
  scanner[1] = nullptr;
  FILE* fp = tmpfile();
  
  // Call the function to fuzz
  scanopt_usage(scanner, fp, const_cast<char*>(usage.c_str()));

  // Cleanup
  fclose(fp);
  
  return 0;
}