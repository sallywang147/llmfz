 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "tpm_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a random number of arguments.
  const int argc = stream.ConsumeIntegralInRange<int>(1, 10);

  // Generate random arguments.
  std::vector<std::string> argv(argc);
  for (int i = 0; i < argc; i++) {
    argv[i] = stream.ConsumeRandomLengthString();
  }

  // Call the function under test.
  tpm_server_main(argc, argv.data());

  return 0;
}