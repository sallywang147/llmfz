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
  static bool initialized = false;
  if (!initialized) {
    gnutls_global_init();
    initialized = true;
  }
  int ret;
  gnutls_session_t session;
  ret = gnutls_init(&session, GNUTLS_CLIENT);
  if (ret != GNUTLS_E_SUCCESS) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
      0,
      provider.remaining_bytes());
  auto next_input = provider.ConsumeBytes<unsigned char>(next_size);

  gnutls_transport_ptr transport =
      gnutls_transport_ptr_wrap(&next_input[0], next_input.size());
  gnutls_transport_set_ptr(session, transport);
  gnutls_transport_set_push_function(session, gnutls_transport_push_ptr);
  gnutls_transport_set_pull_function(session, gnutls_transport_pull_ptr);

  ret = gnutls_handshake(session);
  if (ret != GNUTLS_E_SUCCESS) {
    gnutls_deinit(session);
    return 0;
  }

  ret = recv_handshake_final(session, 1);
  if (ret != GNUTLS_E_SUCCESS) {
    gnutls_deinit(session);
    return 0;
  }

  gnutls_deinit(session);

  return 0;
}

int recv_handshake_final(gnutls_session_t session, int timeout) {
  int ret;
  char buf[4096];
  while ((ret = gnutls_record_recv(session, buf, sizeof(buf))) > 0) {
    if (timeout-- <= 0) {
      return GNUTLS_E_TIMEOUT;
    }
  }
  if (ret == GNUTLS_E_AGAIN) {
    return GNUTLS_E_SUCCESS;
  }
  return ret;
}
```

The code has the following issues:

1. The `recv_handshake_final` function is not defined.

To fix this issue, we define the `recv_handshake_final` function as follows:

```c++
int recv_handshake_final(gnutls_session_t session, int timeout) {
  int ret;
  char buf[4096];
  while ((ret = gnutls_record_recv(session, buf, sizeof(buf))) > 0) {
    if (timeout-- <= 0) {
      return GNUTLS_E_TIMEOUT;
    }
  }
  if (ret == GNUTLS_E_AGAIN) {
    return GNUTLS_E_SUCCESS;
  }
  return ret;
}
```

2. The `gnutls_transport_push_ptr` and `gnutls_transport_pull_ptr` functions are not defined.

To fix this issue, we include the following header file:

```c++
#include <gnutls/gnutls.h>
```

3. The `gnutls_global_init()` function is not defined.

To fix this issue, we include the following header file:

```c++
#include <gnutls/gnutls.h>
```

4. The `gnutls_init()` function is not defined.

To fix this issue, we include the following header file:

```c++
#include <gnutls/gnutls.h>
```

5. The `gnutls_handshake()` function is not defined.

To fix this issue, we include the following header file:

```c++
#include <gnutls/gnutls.h>
```

6. The `gnutls_deinit()` function is not defined.

To fix this issue, we include the following header file:

```c++
#include <gnutls/gnutls.h>