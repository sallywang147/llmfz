#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "ares.h"

// Define the function type
typedef void (*func_type)(void*);

// Define the callback function
void callback(void* arg) {
    return;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct ares_channeldata channeldata;
    struct sockaddr sockaddr;
    int flags = stream.ConsumeIntegral<int>();
    int family = stream.ConsumeIntegral<int>();
    func_type callbackFunc = callback;
    std::string name = stream.ConsumeRandomLengthString();
    char* namePtr = name.c_str();

    // Consume data for channeldata and sockaddr
    stream.ConsumeData(&channeldata, sizeof(channeldata));
    stream.ConsumeData(&sockaddr, sizeof(sockaddr));

    ares_getnameinfo(&channeldata, &sockaddr, flags, family, callbackFunc, namePtr);

    return 0;
}