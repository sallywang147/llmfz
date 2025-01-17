#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "importproject.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::unique_ptr<ImportProject> import_project(new ImportProject());
  std::string sln_file_path = stream.ConsumeRandomLengthString();
  std::string project_path = stream.ConsumeRandomLengthString();
  std::vector<std::string> project_files;
  while (stream.remaining_bytes() > 0) {
    project_files.push_back(stream.ConsumeRandomLengthString());
  }
  std::istringstream sln_file_stream(sln_file_path);
  import_project->importSln(import_project.get(), &sln_file_stream,
                            &project_path, &project_files);
  return 0;
}