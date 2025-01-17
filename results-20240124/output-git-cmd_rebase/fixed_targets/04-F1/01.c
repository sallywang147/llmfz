#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv;
  for (int i = 0; i < argc; i++) {
    argv.emplace_back(stream.ConsumeRandomLengthString());
  }
  char** argv_ptr = new char*[argc];
  for (int i = 0; i < argc; i++) {
    argv_ptr[i] = const_cast<char*>(argv[i].c_str());
  }
  const std::string command = stream.ConsumeRandomLengthString();
  char* command_ptr = const_cast<char*>(command.c_str());
  cmd_rebase(argc, argv_ptr, command_ptr);
  delete[] argv_ptr;
  return 0;
}