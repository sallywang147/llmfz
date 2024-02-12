#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "tpm_server.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegralInRange<int>(1, 10);
  std::vector<std::string> argv_vector;
  for (int i = 0; i < argc; i++) {
    argv_vector.push_back(stream.ConsumeRemainingBytesAsString());
  }
  std::vector<char*> argv;
  for (const std::string& arg : argv_vector) {
    argv.push_back(const_cast<char*>(arg.c_str()));
  }
  tpm_server_main(argc, argv.data());
  return 0;
}