#include <fuzzer/FuzzedDataProvider.h>
#include <civetweb.h>

#include <cstddef>
#include <cstdint>
#include <string>

static int event_handler(struct mg_connection *conn, enum mg_event ev) {
  return MG_FALSE;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const struct mg_callbacks callbacks = { event_handler, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
  const char *options[] = {
    "document_root", ".",
    "listening_ports", "8080",
    nullptr
  };
  struct mg_context *ctx = mg_start(&callbacks, nullptr, options);
  if (ctx == nullptr) {
    return 0;
  }

  struct mg_connection *conn = mg_connect(ctx, "localhost:8080");
  if (conn == nullptr) {
    mg_stop(ctx);
    return 0;
  }

  // Create the path and mime_type variables
  std::string path = stream.ConsumeRandomLengthString();
  std::string mime_type = stream.ConsumeRandomLengthString();

  // Call the function to fuzz
  mg_send_mime_file(conn, const_cast<char *>(path.c_str()), const_cast<char *>(mime_type.c_str()));

  mg_close_connection(conn);
  mg_stop(ctx);

  return 0;
}