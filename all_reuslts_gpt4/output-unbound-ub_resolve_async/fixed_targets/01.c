#include <fuzzer/FuzzedDataProvider.h>
#include <unbound.h>

#include <cstddef>
#include <cstdint>
#include <vector>

// Callback function for unbound resolver
void resolve_callback(void* mydata, int err, struct ub_result* result) {
    // We don't need to do anything here for fuzzing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Create a new resolver context
    struct ub_ctx* ctx = ub_ctx_create();
    if (!ctx) {
        return 0;
    }

    // Consume data to create a name for DNS resolution
    std::string name = stream.ConsumeRandomLengthString();
    if (name.empty()) {
        ub_ctx_delete(ctx);
        return 0;
    }

    // Consume data to create a mydata string
    std::string mydata = stream.ConsumeRemainingBytesAsString();

    // Consume data to create rrtype and rrclass
    int rrtype = stream.ConsumeIntegral<int>();
    int rrclass = stream.ConsumeIntegral<int>();

    int async_id = 0;

    // Call the function to fuzz
    int ret = ub_resolve_async(ctx, const_cast<char*>(name.c_str()), rrtype, rrclass, const_cast<char*>(mydata.c_str()), &resolve_callback, &async_id);

    // Cleanup
    ub_ctx_delete(ctx);

    return 0;
}