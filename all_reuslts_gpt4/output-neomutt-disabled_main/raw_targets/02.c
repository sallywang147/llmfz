#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need at least two arguments for disabled_main.
  if (stream.remaining_bytes() < 2) {
    return 0;
  }

  // Consume first argument.
  std::string arg1 = stream.ConsumeRandomLengthString();
  if (arg1.empty()) {
    return 0;
  }

  // Consume second argument.
  std::string arg2 = stream.ConsumeRemainingBytesAsString();
  if (arg2.empty()) {
    return 0;
  }

  // Prepare the arguments for disabled_main.
  int argc = 3;
  char* argv[] = {
    (char*)"fuzzer",
    (char*)arg1.c_str(),
    (char*)arg2.c_str(),
    nullptr
  };

  // Call the target function.
  disabled_main(argc, argv, nullptr);

  return 0;
}