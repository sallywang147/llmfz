#include <fuzzer/FuzzedDataProvider.h>

#include "proto_tcp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct proto_info pi;
    pi.id = stream.ConsumeIntegral<int>();
    pi.name = stream.ConsumeRandomLengthString().c_str();
    pi.default_port = stream.ConsumeIntegral<unsigned short>();
    pi.default_port_s = stream.ConsumeRandomLengthString().c_str();
    pi.default_port_no = stream.ConsumeIntegral<int>();
    pi.request_no = stream.ConsumeIntegral<int>();
    pi.rpl_no = stream.ConsumeIntegral<int>();
    pi.reserved1 = stream.ConsumeIntegral<int>();
    pi.reserved2 = stream.ConsumeIntegral<int>();

    // Call the function to fuzz
    return proto_tcp_init(&pi);
}