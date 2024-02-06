#include <fuzzer/FuzzedDataProvider.h>
#include <fftw3.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }
  
  FuzzedDataProvider fuzzed_data(data, size);
  
  // Initialize the planner and scanner
  struct planner_s ego;
  struct scanner_s sc;
  
  // Consume the data to the planner and scanner
  size_t consumed = fuzzed_data.ConsumeData(&ego, sizeof(ego));
  if (consumed != sizeof(ego)) {
    return 0;
  }
  consumed = fuzzed_data.ConsumeData(&sc, sizeof(sc));
  if (consumed != sizeof(sc)) {
    return 0;
  }
  
  // Call the target function
  imprt(&ego, &sc);
  
  return 0;
}