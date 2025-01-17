#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

extern int disabled_main(int, char**, char**);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  int argc = 3;
  char *argv[3];
  char *envp[1] = { nullptr };

  std::string arg1 = provider.ConsumeRandomLengthString();
  std::string arg2 = provider.ConsumeRemainingBytesAsString();

  argv[0] = (char*)"fuzzer";
  argv[1] = const_cast<char*>(arg1.c_str());
  argv[2] = const_cast<char*>(arg2.c_str());

  disabled_main(argc, argv, envp);

  return 0;
}