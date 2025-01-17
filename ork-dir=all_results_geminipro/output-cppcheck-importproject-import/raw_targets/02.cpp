#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "importproject.h"
#include "settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string project_path = stream.ConsumeRemainingBytesAsString();
  Settings settings;
  ImportProject import_project;

  int ret = import_project.import(&import_project, &project_path, &settings);
  if (ret != 0) {
    return 0;
  }

  return 0;
}