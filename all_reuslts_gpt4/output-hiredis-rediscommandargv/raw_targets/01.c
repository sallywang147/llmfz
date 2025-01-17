#include "hiredis.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  struct redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL || c->err) {
    if (c) {
      redisFree(c);
    }
    return 0;
  }

  int argc = fuzzed_data.ConsumeIntegralInRange<int>(1, 10);
  char *argv[argc];
  size_t argvlen[argc];

  for (int i = 0; i < argc; i++) {
    std::string arg = fuzzed_data.ConsumeRandomLengthString();
    argv[i] = strdup(arg.c_str());
    argvlen[i] = arg.size();
  }

  redisReply *reply = (redisReply *)redisCommandArgv(c, argc, argv, argvlen);

  freeReplyObject(reply);
  redisFree(c);

  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }

  return 0;
}