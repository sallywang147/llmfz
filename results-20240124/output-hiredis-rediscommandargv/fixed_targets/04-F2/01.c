#include <iostream>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
#include <hiredis/sds.h>
}

int main() {
  redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
  if (c->err) {
    std::cout << "Error: " << c->errstr << std::endl;
    return 1;
  }

  redisAsyncCommand(c, NULL, NULL, "SET key value");
  redisAsyncDisconnect(c);
  return 0;
}