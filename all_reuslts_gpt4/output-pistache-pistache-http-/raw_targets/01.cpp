#include <fuzzer/FuzzedDataProvider.h>
#include <pistache/http.h>
#include <pistache/stream.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create and initialize a Pistache::Http::Uri::Query object
    Pistache::Http::Uri::Query query;

    // Create and initialize a Pistache::ArrayStreamBuf object
    std::vector<uint8_t> buffer = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes());
    Pistache::ArrayStreamBuf arrayStreamBuf(buffer.data(), buffer.size());

    // Call the function under test
    Pistache::Http::encode(query, &arrayStreamBuf);

    return 0;
}