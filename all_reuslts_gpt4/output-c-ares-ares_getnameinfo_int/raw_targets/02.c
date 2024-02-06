#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "ares.h"

typedef void (*func_type)(void);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct ares_channeldata channeldata;
    struct sockaddr_in addr;
    int flags = stream.ConsumeIntegral<int>();
    int addrlen = sizeof(addr);
    func_type callback = nullptr;
    char hostname[NI_MAXHOST];

    // Initialize sockaddr structure
    addr.sin_family = AF_INET;
    addr.sin_port = stream.ConsumeIntegral<uint16_t>();
    addr.sin_addr.s_addr = stream.ConsumeIntegral<uint32_t>();

    ares_getnameinfo_int(&channeldata, (struct sockaddr *)&addr, addrlen, flags, callback, hostname);

    return 0;
}