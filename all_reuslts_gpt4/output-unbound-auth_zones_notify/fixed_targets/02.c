#include <fuzzer/FuzzedDataProvider.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdint>
#include <cstring>

#include "auth_zones.h"
#include "module.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize auth_zones and module_env objects
    struct auth_zones az;
    struct module_env env;

    // Initialize the parameters to be passed to the function
    short dclass = stream.ConsumeIntegral<short>();
    int addrlen = stream.ConsumeIntegral<int>();
    int has_serial = stream.ConsumeBool();
    int serial = stream.ConsumeIntegral<int>();
    int refused = stream.ConsumeIntegral<int>();

    // Consume size for nm and ensure it does not exceed remaining data
    size_t nmlen = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    std::string nm = stream.ConsumeBytesAsString(nmlen);

    // Consume remaining bytes for addr
    std::vector<uint8_t> addr_bytes = stream.ConsumeRemainingBytes<uint8_t>();
    struct sockaddr_storage addr;
    std::memcpy(&addr, addr_bytes.data(), addr_bytes.size());

    // Call the function under test
    auth_zones_notify(&az, &env, nm.data(), nmlen, dclass, &addr, addrlen, has_serial, serial, &refused);

    return 0;
}