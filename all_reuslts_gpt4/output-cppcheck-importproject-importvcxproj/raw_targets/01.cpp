#include <fuzzer/FuzzedDataProvider.h>
#include <set>
#include <vector>
#include <string>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ImportProject importProject;
  std::string projectPath = stream.ConsumeRandomLengthString();
  std::set<std::string> preprocessorDefinitions;
  std::string includePaths = stream.ConsumeRandomLengthString();
  std::vector<std::string> files;

  // Fill the set and vector with random strings.
  while (stream.remaining_bytes() > 0) {
    preprocessorDefinitions.insert(stream.ConsumeRandomLengthString());
    files.push_back(stream.ConsumeRandomLengthString());
  }

  importProject.importVcxproj(&importProject, &projectPath, &preprocessorDefinitions, &includePaths, &files);

  return 0;
}