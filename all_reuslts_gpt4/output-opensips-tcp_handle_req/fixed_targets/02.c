#include <fuzzer/FuzzedDataProvider.h>
#include "tcp_conn.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize tcp_req
    struct tcp_req req;
    req.type = stream.ConsumeIntegral<int>();
    req.complete = stream.ConsumeBool();
    req.has_content_len = stream.ConsumeBool();
    req.content_len = stream.ConsumeIntegral<int>();
    req.start = stream.ConsumeIntegral<int>();
    req.parsed = stream.ConsumeIntegral<int>();
    req.pos = stream.ConsumeIntegral<int>();
    req.bytes_to_go = stream.ConsumeIntegral<int>();
    req.error = stream.ConsumeIntegral<int>();
    req.state = stream.ConsumeIntegral<int>();
    req.b_size = stream.ConsumeIntegral<int>();
    req.body = stream.ConsumeBytes<uint8_t>(req.b_size).data();

    // Initialize tcp_connection
    struct tcp_connection con;
    con.id = stream.ConsumeIntegral<int>();
    con.fd = stream.ConsumeIntegral<int>();
    con.state = stream.ConsumeIntegral<int>();
    con.timeout = stream.ConsumeIntegral<int>();
    con.lifetime = stream.ConsumeIntegral<int>();
    con.con_req = stream.ConsumeIntegral<int>();
    con.msg_attempts = stream.ConsumeIntegral<int>();
    con.id_hash = stream.ConsumeIntegral<int>();
    con.con_lifetime = stream.ConsumeIntegral<int>();
    con.rd_buf = stream.ConsumeBytes<uint8_t>(req.b_size).data();
    con.rd_pos = stream.ConsumeIntegral<int>();
    con.rd_buf_size = stream.ConsumeIntegral<int>();
    con.rd_no = stream.ConsumeIntegral<int>();
    con.wr_no = stream.ConsumeIntegral<int>();

    // Initialize other parameters
    int _max_msg_chunks = stream.ConsumeIntegral<int>();
    int _parallel_handling = stream.ConsumeIntegral<int>();

    // Call the function to fuzz
    tcp_handle_req(&req, &con, _max_msg_chunks, _parallel_handling);

    return 0;
}