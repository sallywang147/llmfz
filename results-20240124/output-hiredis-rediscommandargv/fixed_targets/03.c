#include <iostream>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
#include <hiredis/sds.h>
}

using namespace std;

int main() {
  redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
  if (c->err) {
    cout << "Error: " << c->errstr << endl;
    return 1;
  }

  redisAsyncCommandArgv(c, NULL, NULL, 2, (char*[]) {"SET", "key value"}, NULL);
  redisAsyncCommandArgv(c, NULL, NULL, 2, (char*[]) {"GET", "key"}, NULL);
  redisAsyncDisconnect(c);

  return 0;
}