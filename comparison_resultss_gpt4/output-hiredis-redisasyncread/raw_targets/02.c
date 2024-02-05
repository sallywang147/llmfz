#include "hiredis.h"
#include "async.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  struct redisAsyncContext ac;
  memset(&ac, 0, sizeof(ac));

  ac.c.reader = redisReaderCreate();
  if (ac.c.reader == NULL)
    return 0;

  ac.c.reader->buf = (char*)stream.ConsumeRemainingBytes().data();

  redisAsyncRead(&ac);

  redisReaderFree(ac.c.reader);

  return 0;
}