#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the st_ptls_t struct
  struct st_ptls_t tls;
  memset(&tls, 0, sizeof(tls));

  // Initialize the st_ptls_message_emitter_t struct
  struct st_ptls_message_emitter_t emitter;
  memset(&emitter, 0, sizeof(emitter));

  // Consume some bytes for the message
  std::string message = stream.ConsumeBytesAsString(stream.remaining_bytes());

  // Call the function
  client_handle_finished(&tls, &emitter, message.c_str(), message.size());

  return 0;
}