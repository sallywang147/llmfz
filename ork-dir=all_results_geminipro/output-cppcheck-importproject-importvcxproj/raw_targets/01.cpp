#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "ImportProject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ImportProject import_project;
  const std::string project_file_path = stream.ConsumeRemainingBytesAsString();

  std::string project_name;
  std::set<std::string> project_files;
  std::string project_root;
  std::vector<std::string> project_dependencies;

  import_project.importVcxproj(&import_project, &project_file_path,
                              &project_files, &project_root,
                              &project_dependencies);

  return 0;
}