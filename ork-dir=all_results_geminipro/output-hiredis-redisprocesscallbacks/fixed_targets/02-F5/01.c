#include "hiredis.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

extern "C" {
#include <hiredis/async.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct redisAsyncContext *ac = redisAsyncConnect("127.0.0.1", 6379);
  if (ac == NULL || ac->err) {
    return 0;
  }

  // Set a timeout of 1 second for the connection.
  struct timeval timeout = {1, 0};
  redisAsyncSetConnectTimeout(ac, &timeout);

  // Send a command to the server.
  redisAsyncCommand(ac, NULL, NULL, "SET key %b", data, size);

  // Process the command and wait for a response.
  redisAsyncHandleConnect(ac);
  redisAsyncHandleRead(ac);

  // Free the context.
  redisAsyncFree(ac);

  return 0;
}