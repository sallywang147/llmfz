#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct st_ptls_t tls = {0};
  struct st_ptls_message_emitter_t emitter = {0};

  // Consume a string from the input data
  std::string message = stream.ConsumeRandomLengthString();

  // Call the function under test
  int result = client_handle_finished(&tls, &emitter, message.c_str(), message.size());

  return 0;
}