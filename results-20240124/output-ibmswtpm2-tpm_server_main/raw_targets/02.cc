 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  std::vector<std::string> argv;
  for (int i = 0; i < argc; i++) {
    argv.push_back(stream.ConsumeRemainingBytesAsString());
  }
  std::vector<char*> argv_ptr;
  for (const std::string& arg : argv) {
    argv_ptr.push_back(const_cast<char*>(arg.c_str()));
  }
  tpm_server_main(argc, argv_ptr.data());
  return 0;
}