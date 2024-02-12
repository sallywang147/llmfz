#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "import_project.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  // Create a dummy ImportProject object.
  ImportProject importProject;
  // Create a dummy std::istream object.
  std::stringstream inputStream;
  // Create a dummy std::string object.
  std::string projectName;
  // Create a dummy std::vector object.
  std::vector<std::string> projectFiles;
  // Use the FuzzedDataProvider to generate input for the importSln function.
  std::string slnData = stream.ConsumeRemainingBytesAsString();
  inputStream.str(slnData);
  // Call the importSln function with the generated input.
  bool result = importProject.importSln(&importProject, &inputStream, &projectName,
                                        &projectFiles);
  return 0;
}