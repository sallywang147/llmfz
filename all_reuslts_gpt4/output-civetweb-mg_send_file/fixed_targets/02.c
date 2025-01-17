#include <fuzzer/FuzzedDataProvider.h>
#include <civetweb.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize CivetWeb
  const char *options[] = {
    "document_root", ".",
    "listening_ports", "8080",
    NULL
  };
  struct mg_context *ctx = mg_start(NULL, NULL, options);
  if (ctx == NULL) {
    return 0;
  }

  // Create a connection
  struct mg_connection *conn = mg_connect(ctx, "localhost:8080");
  if (conn == NULL) {
    mg_stop(ctx);
    return 0;
  }

  // Consume data to create a file path
  std::string filePath = stream.ConsumeRandomLengthString();
  char *path = const_cast<char*>(filePath.c_str());

  // Call the function under test
  mg_send_file(conn, path);

  // Clean up
  mg_close_connection(conn);
  mg_stop(ctx);

  return 0;
}