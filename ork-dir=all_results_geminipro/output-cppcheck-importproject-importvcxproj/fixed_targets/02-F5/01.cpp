#include <fuzzer/FuzzedDataProvider.h>
#include <vector>
#include <set>

extern "C" {
#include <windows.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string project_path = stream.ConsumeRemainingBytesAsString();
  std::string project_name = stream.ConsumeRemainingBytesAsString();
  std::set<std::string> project_files;
  std::vector<std::string> project_includes;
  ImportProject import_project;
  import_project.importVcxproj(nullptr, &project_path, &project_files, &project_name,
                               &project_includes);
  return 0;
}

#include "importproject.h"

void ImportProject::importVcxproj(const std::string *vcxproj_path,
                                  const std::string *project_path,
                                  std::set<std::string> *project_files,
                                  std::string *project_name,
                                  std::vector<std::string> *project_includes) {
  // Function implementation
}