 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int argc = stream.ConsumeIntegral<int>();
  char** argv = new char*[argc];
  for (int i = 0; i < argc; ++i) {
    const size_t arg_size = stream.ConsumeIntegralInRange<size_t>(1, 100);
    argv[i] = new char[arg_size + 1];
    strncpy(argv[i], stream.ConsumeBytesAsString(arg_size).c_str(), arg_size);
    argv[i][arg_size] = '\0';
  }

  init(argc, argv);

  for (int i = 0; i < argc; ++i) {
    delete[] argv[i];
  }
  delete[] argv;

  return 0;
}