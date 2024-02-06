#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <ares.h>

extern "C" {
#include <ares_version.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ares_library_init(ARES_LIB_INIT_ALL);
    initialized = true;
  }

  ares_channel channel;
  int status = ares_init(&channel);
  if (status != ARES_SUCCESS) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::vector<char> name_buffer(provider.ConsumeIntegralInRange<size_t>(0, 1024));
  provider.ConsumeBytes(name_buffer.data(), name_buffer.size());
  std::vector<char> service_buffer(provider.ConsumeIntegralInRange<size_t>(0, 1024));
  provider.ConsumeBytes(service_buffer.data(), service_buffer.size());

  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = provider.ConsumeIntegralInRange<int>(0, 4);
  hints.ai_socktype = provider.ConsumeIntegralInRange<int>(0, 4);
  hints.ai_protocol = provider.ConsumeIntegralInRange<int>(0, 4);
  hints.ai_flags = provider.ConsumeIntegralInRange<int>(0, 4);

  struct ares_addrinfo *result;
  status = ares_getaddrinfo(channel, name_buffer.data(), service_buffer.data(), &hints,
                            NULL, &result); // Change nullptr to NULL
  if (status == ARES_SUCCESS) {
    ares_free_addrinfo(result);
  }

  ares_destroy(channel);

  return 0;
}