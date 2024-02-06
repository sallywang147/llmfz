#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "importproject.h"
#include "settings.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ImportProject importProject;
  Settings settings;

  std::string str = stream.ConsumeRandomLengthString();
  importProject.import(&importProject, &str, &settings);

  return 0;
}