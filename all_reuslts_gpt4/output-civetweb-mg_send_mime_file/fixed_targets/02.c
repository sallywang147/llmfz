#include <fuzzer/FuzzedDataProvider.h>
#include <civetweb.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a civetweb server.
    const char *options[] = {
        "document_root", ".",
        "listening_ports", "8080",
        0
    };
    struct mg_context *ctx = mg_start(NULL, 0, options);
    if (ctx == NULL) {
        return 0;
    }

    // Get a connection.
    struct mg_connection *conn = mg_connect(ctx, "localhost:8080");
    if (conn == NULL) {
        mg_stop(ctx);
        return 0;
    }

    // Get path and mime_type from the fuzzer.
    std::string path = fuzzed_data.ConsumeRandomLengthString();
    std::string mime_type = fuzzed_data.ConsumeRandomLengthString();

    // Call the function to be fuzzed.
    mg_send_mime_file(conn, const_cast<char *>(path.c_str()), const_cast<char *>(mime_type.c_str()));

    // Clean up.
    mg_close_connection(conn);
    mg_stop(ctx);

    return 0;
}