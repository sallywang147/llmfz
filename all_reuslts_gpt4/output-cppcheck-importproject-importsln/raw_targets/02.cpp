#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string data_str = stream.ConsumeRemainingBytesAsString();
  std::istringstream data_stream(data_str);

  ImportProject project;
  std::string path;
  std::vector<std::string> configuration;

  project.importSln(&project, &data_stream, &path, &configuration);

  return 0;
}