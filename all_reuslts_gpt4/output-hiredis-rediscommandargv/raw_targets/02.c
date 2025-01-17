#include <fuzzer/FuzzedDataProvider.h>
#include "hiredis.h"
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0;
    }

    FuzzedDataProvider fuzzed_data(data, size);

    // Create a redis context
    struct redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            redisFree(c);
        }
        return 0;
    }

    std::vector<char*> argv;
    std::vector<size_t> argvlen;

    while (fuzzed_data.remaining_bytes() > 0) {
        std::string arg = fuzzed_data.ConsumeRandomLengthString();
        argv.push_back(const_cast<char*>(arg.c_str()));
        argvlen.push_back(arg.size());
    }

    // Call the target function
    char *reply = redisCommandArgv(c, argv.size(), argv.data(), argvlen.data());

    // Free the reply object
    if (reply != NULL) {
        freeReplyObject(reply);
    }

    // Free the redis context
    redisFree(c);

    return 0;
}