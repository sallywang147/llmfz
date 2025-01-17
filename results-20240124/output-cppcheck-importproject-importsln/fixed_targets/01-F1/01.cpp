#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "import_project.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::unique_ptr<ImportProject> import_project(new ImportProject());
  std::string solution_path = stream.ConsumeRemainingBytesAsString();
  std::vector<std::string> solution_files = stream.ConsumeRemainingBytesAsString().split('\n');
  std::string project_path = stream.ConsumeRemainingBytesAsString();
  std::vector<std::string> project_files = stream.ConsumeRemainingBytesAsString().split('\n');
  std::string project_name = stream.ConsumeRemainingBytesAsString();
  std::string project_type = stream.ConsumeRemainingBytesAsString();
  std::string project_guid = stream.ConsumeRemainingBytesAsString();
  std::string project_version = stream.ConsumeRemainingBytesAsString();
  std::string project_configuration = stream.ConsumeRemainingBytesAsString();
  std::string project_platform = stream.ConsumeRemainingBytesAsString();
  std::string project_output_path = stream.ConsumeRemainingBytesAsString();
  std::string project_intermediate_path = stream.ConsumeRemainingBytesAsString();
  std::string project_resource_path = stream.ConsumeRemainingBytesAsString();
  std::string project_preprocessor_definitions = stream.ConsumeRemainingBytesAsString();
  std::string project_include_directories = stream.ConsumeRemainingBytesAsString();
  std::string project_library_directories = stream.ConsumeRemainingBytesAsString();
  std::string project_additional_dependencies = stream.ConsumeRemainingBytesAsString();
  std::string project_additional_link_flags = stream.ConsumeRemainingBytesAsString();
  std::string project_additional_compile_flags = stream.ConsumeRemainingBytesAsString();
  std::string project_target_name = stream.ConsumeRemainingBytesAsString();
  std::string project_target_type = stream.ConsumeRemainingBytesAsString();
  std::string project_target_platform = stream.ConsumeRemainingBytesAsString();
  std::string project_target_configuration = stream.ConsumeRemainingBytesAsString();
  std::string project_target_output_path = stream.ConsumeRemainingBytesAsString();
  std::string project_target_intermediate_path = stream.ConsumeRemainingBytesAsString();
  std::string project_target_resource_path = stream.ConsumeRemainingBytesAsString();
  std::string project_target_preprocessor_definitions = stream.ConsumeRemainingBytesAsString();
  std::string project_target_include_directories = stream.ConsumeRemainingBytesAsString();
  std::string project_target_library_directories = stream.ConsumeRemainingBytesAsString();
  std::string project_target_additional_dependencies = stream.ConsumeRemainingBytesAsString();
  std::string project_target_additional_link_flags = stream.ConsumeRemainingBytesAsString();
  std::string project_target_additional_compile_flags = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_name = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_type = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_platform = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_configuration = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_output_path = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_intermediate_path = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_resource_path = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_preprocessor_definitions = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_include_directories = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_library_directories = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_additional_dependencies = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_additional_link_flags = stream.ConsumeRemainingBytesAsString();
  std::string project_target_target_additional_compile_flags = stream.ConsumeRemainingBytesAsString();

  import_project->importSln(import_project.get(), &std::cin, &solution_path, &solution_files);
  return 0;
}