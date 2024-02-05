#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int main2(int argc, char **argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // The first byte is used to determine the number of arguments (argc).
  // The maximum number of arguments is limited to 10 for simplicity.
  int argc = stream.ConsumeIntegralInRange<int>(0, 10);
  char* argv[argc + 1];

  // The rest of the input is used to generate the arguments (argv).
  for (int i = 0; i < argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv[i] = const_cast<char*>(arg.c_str());
  }

  // The last element of argv must be a null pointer.
  argv[argc] = nullptr;

  // Call the target function.
  main2(argc, argv);

  return 0;
}