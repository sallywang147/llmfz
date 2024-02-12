 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class ImportProject {
public:
  bool importSln(ImportProject*, std::istream*, std::string*, std::vector*);
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string sln_file = stream.ConsumeRemainingBytesAsString();
  std::ifstream in(sln_file);
  if (!in.is_open()) {
    return 0;
  }

  std::string solution_filename = stream.ConsumeRemainingBytesAsString();
  std::vector<std::string> project_filenames;
  ImportProject import_project;
  import_project.importSln(nullptr, &in, &solution_filename, &project_filenames);
  return 0;
}