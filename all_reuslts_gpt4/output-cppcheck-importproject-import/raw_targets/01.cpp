#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ImportProject object
  ImportProject importProject;

  // Extract string
  std::string str = stream.ConsumeRandomLengthString();
  
  // Initialize Settings object
  Settings settings;

  // Call the target function
  importProject.import(&importProject, &str, &settings);

  return 0;
}