#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int argc = provider.ConsumeIntegralInRange<int>(0, 10);
  char **argv = (char **)calloc(argc + 1, sizeof(char *));
  for (int i = 0; i < argc; i++) {
    size_t arg_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    argv[i] = (char *)calloc(arg_size + 1, sizeof(char));
    provider.ConsumeBytes<char>(argv[i], arg_size);
  }
  char **envp = (char **)calloc(1, sizeof(char *));
  disabled_main(argc, argv, envp);
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  free(argv);
  free(envp);
  return 0;
}