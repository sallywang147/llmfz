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
  import_project.ImportSln(&input_stream);

  return 0;
}

bool ImportProject::ImportSln(std::istream *input_stream, std::string *output, std::vector *errors) {
  // Implementation of the function
}