#include <redis.h>
#include <iostream>

using namespace std;

extern "C" {
#include <hiredis/hiredis.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL) {
        cout << "Connection error!" << endl;
        return 0;
    }

    redisReply *reply = (redisReply *)redisCommand(c, "PING");
    if (reply == NULL) {
        cout << "Command error!" << endl;
        redisFree(c);
        return 0;
    }

    cout << "Server response: " << reply->str << endl;
    freeReplyObject(reply);
    redisFree(c);

    return 0;
}

int main() {
    return 0;
}