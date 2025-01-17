#include <fuzzer/FuzzedDataProvider.h>

#ifdef __cplusplus
extern "C" {
#endif
size_t FC_Initialize(char *);
#ifdef __cplusplus
}
#endif

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRandomLengthString(size);
  char *ptr = str.c_str();
  FC_Initialize(ptr);
  return 0;
}
```

This code wraps the declaration of `FC_Initialize` with `extern "C" {}` to ensure that it is compatible with C++ compilers and linkers. This resolves the undefined reference error.