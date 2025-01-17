#include <fuzzer/FuzzedDataProvider.h>
#include <event2/event.h>
#include <event2/http.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Consume data for parameters
    std::string address = stream.ConsumeRandomLengthString();
    short port = stream.ConsumeIntegral<short>();

    // Call the function
    struct evhttp *http = evhttp_start(address.c_str(), port);

    // Clean up
    if (http != nullptr) {
        evhttp_free(http);
    }

    return 0;
}