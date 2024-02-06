#include <fuzzer/FuzzedDataProvider.h>
#include "../tcp_conn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize tcp_connection struct
    struct tcp_connection con = {};
    con.id = stream.ConsumeIntegral<int>();
    con.fd = stream.ConsumeIntegral<int>();
    con.state = stream.ConsumeIntegral<int>();
    con.extra_data = (void*)stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();

    // Initialize bytes_read variable
    int bytes_read = stream.ConsumeIntegral<int>();

    // Call the function to fuzz
    tcp_read_req(&con, &bytes_read);

    return 0;
}