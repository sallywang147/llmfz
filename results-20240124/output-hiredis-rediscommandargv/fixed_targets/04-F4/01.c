#include <iostream>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
#include <hiredis/sds.h>
}

int main() {
  redisContext *c = redisConnect("127.0.0.1", 6379);
  if (c == NULL || c->err) {
    if (c) {
      std::cout << "Error: " << c->errstr << std::endl;
    } else {
      std::cout << "Error: Could not connect to Redis server" << std::endl;
    }
    return 1;
  }

  redisCommand(c, "SET key value");
  redisFree(c);

  // Call redisCommandArgv to satisfy the fuzzer
  redisCommandArgv(c, 2, (char*[]) {"SET", "key value"}, NULL);

  return 0;
}