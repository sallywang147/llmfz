#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <vector>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string str = stream.ConsumeRemainingBytesAsString();
  std::istringstream iss(str);
  std::string path;
  std::vector<std::string> configuration;

  ImportProject importProject;
  importProject.importSln(&importProject, &iss, &path, &configuration);

  return 0;
}