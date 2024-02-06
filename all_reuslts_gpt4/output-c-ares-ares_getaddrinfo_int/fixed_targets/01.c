#include <stddef.h>
#include "ares.h"
#include "fuzzer/FuzzedDataProvider.h"

// Mock implementation of the callback function
void mock_callback(void *arg, int status, int timeouts, struct ares_addrinfo *host) {
  // Do nothing
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ares_channeldata
  struct ares_channeldata channeldata;

  // Consume data for node and service
  std::string node = stream.ConsumeRandomLengthString();
  std::string service = stream.ConsumeRandomLengthString();

  // Initialize ares_addrinfo_hints
  struct ares_addrinfo_hints hints;
  hints.ai_flags = stream.ConsumeIntegral<int>();
  hints.ai_family = stream.ConsumeIntegral<int>();
  hints.ai_socktype = stream.ConsumeIntegral<int>();
  hints.ai_protocol = stream.ConsumeIntegral<int>();

  // Consume data for arg
  std::string arg = stream.ConsumeRandomLengthString();

  // Call the function to fuzz
  ares_getaddrinfo_int(&channeldata, node.c_str(), service.c_str(), &hints, mock_callback, arg.c_str());

  return 0;
}