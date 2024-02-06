#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <fuzzer/FuzzedDataProvider.h>

#ifdef __cplusplus
}
#endif

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  FuzzedDataProvider stream(argv[0], strlen(argv[0]));
  stream.ConsumeRemainingBytes();
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  return 0;
}