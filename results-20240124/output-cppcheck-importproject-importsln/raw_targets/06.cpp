 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input = stream.ConsumeRemainingBytesAsString();
  std::istringstream input_stream(input);

  ImportProject import_project;
  std::string project_path;
  std::vector<std::string> solution_files;
  import_project.importSln(&import_project, &input_stream, &project_path,
                          &solution_files);

  return 0;
}