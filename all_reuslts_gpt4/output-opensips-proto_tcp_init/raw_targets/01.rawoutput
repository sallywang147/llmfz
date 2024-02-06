#include <fuzzer/FuzzedDataProvider.h>
#include "../net/proto_tcp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct proto_info pi;

    // Consume data for the proto_info structure
    pi.id = stream.ConsumeIntegral<short>();
    pi.name = stream.ConsumeRandomLengthString().c_str();
    pi.default_port = stream.ConsumeIntegral<unsigned short>();
    pi.default_port_no = stream.ConsumeIntegral<unsigned short>();
    pi.default_proto = stream.ConsumeIntegral<unsigned short>();
    pi.default_proto_no = stream.ConsumeIntegral<unsigned short>();
    pi.reserved1 = stream.ConsumeIntegral<unsigned short>();
    pi.reserved2 = stream.ConsumeIntegral<unsigned short>();

    // Call the function to fuzz
    proto_tcp_init(&pi);

    return 0;
}