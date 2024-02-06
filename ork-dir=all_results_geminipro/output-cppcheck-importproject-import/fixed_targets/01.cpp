#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "settings.h"

extern "C" {
#include "importproject.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string project_path = stream.ConsumeRemainingBytesAsString();
  ImportProject import_project;
  Settings settings;
  import_project.import(nullptr, &project_path, &settings);
  return 0;
}