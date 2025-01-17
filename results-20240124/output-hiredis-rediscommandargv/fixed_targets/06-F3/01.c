#include <fuzzer/FuzzedDataProvider.h>

#include <stdlib.h>
#include <string.h>
#include "hiredis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t argc = stream.ConsumeIntegral<size_t>();
  if (argc > 10) {
    return 0;
  }
  char **argv = (char**)malloc(sizeof(char*) * argc);
  size_t *argvlen = (size_t*)malloc(sizeof(size_t) * argc);
  for (size_t i = 0; i < argc; i++) {
    argv[i] = (char*)stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 100)).data();
    argvlen[i] = strlen(argv[i]);
  }
  redisContext *c = redisConnect("127.0.0.1", 6379);
  redisCommandArgv(c, argc, (const char**)argv, argvlen);
  redisFree(c);
  free(argv);
  free(argvlen);
  return 0;
}