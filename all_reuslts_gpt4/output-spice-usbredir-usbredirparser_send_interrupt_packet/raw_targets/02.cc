#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "usbredirparser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct usbredirparser *parser = usbredirparser_create(NULL, NULL, 0);
    if (!parser) {
        return 0;
    }

    size_t endpoint = stream.ConsumeIntegral<size_t>();
    struct usb_redir_iso_packet_header iso_packet_header;
    int length = stream.ConsumeIntegral<int>();

    if (length < 0 || static_cast<size_t>(length) > stream.remaining_bytes()) {
        usbredirparser_destroy(parser);
        return 0;
    }

    std::string buffer = stream.ConsumeBytesAsString(length);

    usbredirparser_send_interrupt_packet(parser, endpoint, &iso_packet_header, buffer.data(), length);

    usbredirparser_destroy(parser);
    return 0;
}