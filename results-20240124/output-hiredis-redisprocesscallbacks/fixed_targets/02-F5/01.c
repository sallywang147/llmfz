#include <iostream>
#include <hiredis/hiredis.h>

extern "C" {
#include <hiredis/async.h>
}

using namespace std;

void connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        cout << "Error connecting to Redis: " << c->errstr << endl;
        return;
    }

    cout << "Connected to Redis" << endl;
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        cout << "Error disconnecting from Redis: " << c->errstr << endl;
        return;
    }

    cout << "Disconnected from Redis" << endl;
}

void commandCallback(redisAsyncContext *c, void *r, void *privdata) {
    redisReply *reply = (redisReply *)r;
    if (reply == NULL) return;

    cout << "Received reply from Redis: " << reply->str << endl;
}

int main() {
    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c == NULL) {
        cout << "Error connecting to Redis" << endl;
        return 1;
    }

    redisAsyncSetConnectCallback(c, connectCallback);
    redisAsyncSetDisconnectCallback(c, disconnectCallback);
    redisAsyncCommand(c, commandCallback, NULL, "PING");

    // Call redisProcessCallbacks() to process pending events
    redisProcessCallbacks(c);

    redisAsyncFree(c);

    return 0;
}