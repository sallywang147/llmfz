#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int tpm_server_main(int argc, char ** argv);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int MAX_ARGS = 5;
  int argc = stream.ConsumeIntegralInRange(1, MAX_ARGS);
  char* argv[MAX_ARGS];

  for (int i = 0; i < argc; ++i) {
    std::string arg = stream.ConsumeRandomLengthString();
    argv[i] = strdup(arg.c_str());
  }

  tpm_server_main(argc, argv);

  for (int i = 0; i < argc; ++i) {
    free(argv[i]);
  }

  return 0;
}