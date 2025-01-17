#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the required parameters
  ptls_context_t ctx = {};
  ptls_t *tls = ptls_new(&ctx, 0);
  ptls_buffer_t sendbuf;
  ptls_buffer_init(&sendbuf, "", 0);
  size_t epoch_offsets[5] = {};
  size_t in_epoch = stream.ConsumeIntegral<size_t>();
  std::string input = stream.ConsumeRandomLengthString();
  ptls_handshake_properties_t properties = {};

  // Call the function to fuzz
  ptls_server_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, const_cast<char *>(input.c_str()), input.size(), &properties);

  // Cleanup
  ptls_free(tls);
  ptls_buffer_dispose(&sendbuf);

  return 0;
}