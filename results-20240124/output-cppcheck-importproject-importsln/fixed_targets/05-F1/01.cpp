#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "ImportProject.h"

extern "C" {
#include "ImportProject.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string sln_file = stream.ConsumeRemainingBytesAsString();
  std::vector<std::string> files;
  std::string project_name;
  std::stringstream sln_stream(sln_file);
  ImportProject import_project;
  bool ret = import_project.importSln(nullptr, &sln_stream, &project_name, &files);
  return 0;
}