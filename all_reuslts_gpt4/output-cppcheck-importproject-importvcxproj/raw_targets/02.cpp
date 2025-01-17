#include <fuzzer/FuzzedDataProvider.h>
#include <set>
#include <string>
#include <vector>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ImportProject importProject;
  std::string path = stream.ConsumeRandomLengthString();
  std::set<std::string> data_set;
  std::string configuration = stream.ConsumeRandomLengthString();
  std::vector<std::string> platform;

  importProject.importVcxproj(&importProject, &path, &data_set, &configuration, &platform);

  return 0;
}