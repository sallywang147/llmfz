#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  char** argv = static_cast<char**>(calloc(argc + 1, sizeof(char*)));
  for (int i = 0; i < argc; ++i) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv[i] = strdup(arg.c_str());
  }
  // Call the main function with the generated arguments
  int ret = main2(argc, argv); // Call the main2 function instead of main
  for (int i = 0; i < argc; ++i) {
    free(argv[i]);
  }
  free(argv);
  return ret;
}