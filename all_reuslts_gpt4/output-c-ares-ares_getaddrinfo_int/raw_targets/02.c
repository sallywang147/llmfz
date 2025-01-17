#include <stddef.h>
#include "ares.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ares library
  ares_library_init(ARES_LIB_INIT_ALL);

  // Create ares_channeldata
  struct ares_channeldata *channel;
  ares_init(&channel);

  // Consume data for node and service
  std::string node = stream.ConsumeRandomLengthString();
  std::string service = stream.ConsumeRandomLengthString();

  // Create ares_addrinfo_hints
  struct ares_addrinfo_hints hints;
  hints.ai_flags = stream.ConsumeIntegral<int>();
  hints.ai_family = stream.ConsumeIntegral<int>();
  hints.ai_socktype = stream.ConsumeIntegral<int>();
  hints.ai_protocol = stream.ConsumeIntegral<int>();

  // Create a dummy function for callback
  using func_type = void (*)(void *, int, int, struct ares_addrinfo *);
  func_type callback = [](void *, int, int, struct ares_addrinfo *) {};

  // Consume data for userdata
  std::string userdata = stream.ConsumeRandomLengthString();

  // Call the target function
  ares_getaddrinfo_int(channel, node.c_str(), service.c_str(), &hints, callback, userdata.c_str());

  // Cleanup
  ares_destroy(channel);
  ares_library_cleanup();

  return 0;
}