#include <iostream>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
}

using namespace std;

int main() {
  redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
  if (c->err) {
    cout << "Error: " << c->errstr << endl;
    return 1;
  }

  redisAsyncCommand(c, NULL, NULL, "SET key value");
  redisAsyncCommand(c, NULL, NULL, "GET key");
  redisAsyncDisconnect(c);

  return 0;
}