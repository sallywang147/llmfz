#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <gnutls/gnutls.h>

extern "C" {
#include <gnutls/gnutls.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  gnutls_session_int session;
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_set_default_priority(&session);

  struct mbuffer_st *packet = nullptr;
  size_t packet_size = provider.ConsumeIntegralInRange<size_t>(0, 1<<20);
  auto packet_data = provider.ConsumeBytes<unsigned char>(packet_size);
  gnutls_record_recv_packet(&session, &packet);
  gnutls_record_recv(&session, packet_data.data(), packet_data.size());
  gnutls_deinit(&session);
  return 0;
}
```

In this fixed code, the `gnutls.h` header is included twice, once with `extern "C" {}` and once without. This is necessary because the `gnutls.h` header contains both C and C++ declarations, and the compiler needs to be able to distinguish between the two.

The `extern "C" {}` directive tells the compiler to treat the contents of the block as C code, even though it is in a C++ file. This is necessary because the `gnutls.h` header contains some C declarations that are not compatible with C++.

By including the `gnutls.h` header twice, once with `extern "C" {}` and once without, we ensure that the compiler can correctly parse and compile the header.