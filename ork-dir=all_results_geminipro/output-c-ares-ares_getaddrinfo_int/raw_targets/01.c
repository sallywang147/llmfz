#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ares.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ares_library_init(ARES_LIB_INIT_ALL);
    initialized = true;
  }

  struct ares_channeldata channel;
  ares_channel(&channel);

  std::vector<uint8_t> name_buffer(size);
  std::vector<uint8_t> service_buffer(size);

  FuzzedDataProvider provider(data, size);
  const size_t name_size =
      provider.ConsumeIntegralInRange<size_t>(0, size);
  const size_t service_size =
      provider.ConsumeIntegralInRange<size_t>(0, size);
  auto name = provider.ConsumeBytes<unsigned char>(name_size);
  auto service = provider.ConsumeBytes<unsigned char>(service_size);
  std::memcpy(name_buffer.data(), name.data(), name_size);
  std::memcpy(service_buffer.data(), service.data(), service_size);

  struct ares_addrinfo_hints hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;

  ares_getaddrinfo_int(&channel, reinterpret_cast<char*>(name_buffer.data()),
                       reinterpret_cast<char*>(service_buffer.data()), &hints,
                       nullptr, nullptr);

  ares_destroy(&channel);

  return 0;
}