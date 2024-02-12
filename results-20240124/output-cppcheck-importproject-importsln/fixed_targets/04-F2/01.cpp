#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ImportProject import_project;
  std::string sln_path;
  std::vector<std::string> import_paths;
  import_project.ImportSln(&stream, &sln_path, &import_paths);
  return 0;
}