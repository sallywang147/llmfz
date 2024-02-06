#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <libssh2.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    libssh2_init(0);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  LIBSSH2_SESSION* session = libssh2_session_init();
  if (session == nullptr) {
    return 0;
  }

  std::vector<uint8_t> data_buffer(provider.ConsumeIntegralInRange<size_t>(
      0, std::min(size, static_cast<size_t>(1 << 16))));
  std::copy(provider.ConsumeBytes<uint8_t>(data_buffer.size()).begin(),
            provider.ConsumeBytes<uint8_t>(data_buffer.size()).end(),
            data_buffer.begin());

  std::vector<uint8_t> public_key(provider.ConsumeIntegralInRange<size_t>(
      0, std::min(size, static_cast<size_t>(1 << 16))));
  std::copy(provider.ConsumeBytes<uint8_t>(public_key.size()).begin(),
            provider.ConsumeBytes<uint8_t>(public_key.size()).end(),
            public_key.begin());

  std::vector<uint8_t> private_key(provider.ConsumeIntegralInRange<size_t>(
      0, std::min(size, static_cast<size_t>(1 << 16))));
  std::copy(provider.ConsumeBytes<uint8_t>(private_key.size()).begin(),
            provider.ConsumeBytes<uint8_t>(private_key.size()).end(),
            private_key.begin());

  std::vector<uint8_t> exchange_state(provider.ConsumeIntegralInRange<size_t>(
      0, std::min(size, static_cast<size_t>(1 << 16))));
  std::copy(provider.ConsumeBytes<uint8_t>(exchange_state.size()).begin(),
            provider.ConsumeBytes<uint8_t>(exchange_state.size()).end(),
            exchange_state.begin());

  curve25519_sha256(session, reinterpret_cast<char*>(data_buffer.data()),
                    data_buffer.size(), reinterpret_cast<char*>(public_key.data()),
                    reinterpret_cast<char*>(private_key.data()),
                    reinterpret_cast<struct kmdhgGPshakex_state_t*>(
                        exchange_state.data()));

  libssh2_session_free(session);

  return 0;
}