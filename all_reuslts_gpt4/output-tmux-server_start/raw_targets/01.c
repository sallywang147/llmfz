#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct tmuxproc client;
    int flags = stream.ConsumeIntegral<int>();
    struct event_base *base = event_base_new(); // Initialize libevent base
    int lockfd = stream.ConsumeIntegral<int>();
    std::string lockfile = stream.ConsumeRandomLengthString();
    
    // Call the function to be fuzzed
    server_start(&client, flags, base, lockfd, lockfile.c_str());

    event_base_free(base); // Clean up libevent base

    return 0;
}