#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "httpd.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Allocate a new connection record.
  conn_rec* c = static_cast<conn_rec*>(calloc(1, sizeof(conn_rec)));
  if (c == nullptr) {
    return 0;
  }

  // Initialize the connection record.
  c->client_socket = stream.ConsumeIntegral<int>();
  c->local_addr = stream.ConsumeBytes<sockaddr_in>(sizeof(sockaddr_in));
  c->remote_addr = stream.ConsumeBytes<sockaddr_in>(sizeof(sockaddr_in));
  c->notes = stream.ConsumeBytes<void>(stream.ConsumeIntegralInRange(0, 1000));
  c->notes_length = stream.ConsumeIntegral<size_t>();

  // Call the function to be fuzzed.
  int result = ap_process_http_sync_connection(c);

  // Free the connection record.
  free(c->notes);
  free(c);

  return result;
}