 #include <fuzzer/FuzzedDataProvider.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tpm_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int argc = stream.ConsumeIntegral<int>();
  char **argv = new char*[argc + 1];
  for (int i = 0; i < argc; i++) {
    size_t len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
    argv[i] = new char[len + 1];
    stream.ConsumeBytes<char>(argv[i], len);
    argv[i][len] = '\0';
  }
  argv[argc] = nullptr;

  int ret = tpm_server_main(argc, argv);

  for (int i = 0; i < argc; i++) {
    delete[] argv[i];
  }
  delete[] argv;

  return ret;
}