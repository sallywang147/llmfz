#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
void init(int argc, char** argv);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int argc = stream.ConsumeIntegral<int>();
  char** argv = (char**)malloc(sizeof(char*) * argc);
  for (int i = 0; i < argc; i++) {
    const std::string arg = stream.ConsumeRemainingBytesAsString();
    argv[i] = (char*)malloc(arg.size() + 1);
    strcpy(argv[i], arg.c_str());
  }
  init(argc, argv);
  main(argc, argv);
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  free(argv);
  return 0;
}