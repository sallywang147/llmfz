#include <iostream>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
#include <hiredis/hiredis_ext.h>
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
  redisAsyncCommand(c, NULL, NULL, "QUIT");

  redisAsyncSetConnectCallback(c, [](const redisAsyncContext *ac, int status) {
    if (status != REDIS_OK) {
      cout << "Error connecting to Redis: " << ac->errstr << endl;
      return;
    }

    cout << "Connected to Redis" << endl;
  });

  redisAsyncSetDisconnectCallback(c, [](const redisAsyncContext *ac, int status) {
    if (status != REDIS_OK) {
      cout << "Error disconnecting from Redis: " << ac->errstr << endl;
      return;
    }

    cout << "Disconnected from Redis" << endl;
  });

  redisAsyncSetReplyCallback(c, [](redisAsyncContext *ac, void *r, void *privdata) {
    redisReply *reply = (redisReply *)r;

    if (reply == NULL) {
      return;
    }

    cout << "Received reply: " << reply->str << endl;

    freeReplyObject(reply);
  });

  while (1) {
    redisProcessCallbacks(c);
  }

  redisAsyncFree(c);

  return 0;
}