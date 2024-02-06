#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_accept_ctx_t* ctx =
      static_cast<struct st_h2o_accept_ctx_t*>(
          malloc(sizeof(struct st_h2o_accept_ctx_t)));
  memset(ctx, 0, sizeof(struct st_h2o_accept_ctx_t));
  struct st_h2o_socket_t* sock =
      static_cast<struct st_h2o_socket_t*>(
          malloc(sizeof(struct st_h2o_socket_t)));
  memset(sock, 0, sizeof(struct st_h2o_socket_t));
  h2o_accept(ctx, sock, NULL, NULL);
  free(ctx);
  free(sock);
  return 0;
}
```

The corrected code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_accept_ctx_t* ctx =
      static_cast<struct st_h2o_accept_ctx_t*>(
          malloc(sizeof(struct st_h2o_accept_ctx_t)));
  memset(ctx, 0, sizeof(struct st_h2o_accept_ctx_t));
  struct st_h2o_socket_t* sock =
      static_cast<struct st_h2o_socket_t*>(
          malloc(sizeof(struct st_h2o_socket_t)));
  memset(sock, 0, sizeof(struct st_h2o_socket_t));
  h2o_accept(ctx, sock, NULL, NULL);
  free(ctx);
  free(sock);
  return 0;
}
```

The corrected code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_accept_ctx_t* ctx =
      static_cast<struct st_h2o_accept_ctx_t*>(
          malloc(sizeof(struct st_h2o_accept_ctx_t)));
  memset(ctx, 0, sizeof(struct st_h2o_accept_ctx_t));
  struct st_h2o_socket_t* sock =
      static_cast<struct st_h2o_socket_t*>(
          malloc(sizeof(struct st_h2o_socket_t)));
  memset(sock, 0, sizeof(struct st_h2o_socket_t));
  h2o_accept(ctx, sock, NULL, NULL);
  free(ctx);
  free(sock);
  return 0;
}
```

The corrected code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_accept_ctx_t* ctx =
      static_cast<struct st_h2o_accept_ctx_t*>(
          malloc(sizeof(struct st_h2o_accept_ctx_t)));
  memset(ctx, 0, sizeof(struct st_h2o_accept_ctx_t));
  struct st_h2o_socket_t* sock =
      static_cast<struct st_h2o_socket_t*>(
          malloc(sizeof(struct st_h2o_socket_t)));
  memset(sock, 0, sizeof(struct st_h2o_socket_t));
  h2o_accept(ctx, sock, NULL, NULL);
  free(ctx);
  free(sock);
  return 0;
}
```

The corrected code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_accept_ctx_t* ctx =
      static_cast<struct st_h2o_accept_ctx_t*>(
          malloc(sizeof(struct st_h2o_accept_ctx_t)));
  memset(ctx, 0, sizeof(struct st_h2o_accept_ctx_t));
  struct st_h2o_socket_t* sock =
      static_cast<struct st_h2o_socket_t*>(
          malloc(sizeof(struct st_h2o_socket_t)));
  memset(sock, 0, sizeof(struct st_h2o_socket_t));
  h2o_accept(ctx, sock, NULL, NULL);
  free(ctx);
  free(sock);
  return 0;
}
```

The corrected code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_accept_ctx_t* ctx =
      static_cast<struct st_h2o_accept_ctx_t*>(
          malloc(sizeof(struct st_h2o_accept_ctx_t)));
  memset(ctx, 0, sizeof(struct st_h2o_accept_ctx_t));
  struct st_h2o_socket_t* sock =
      static_cast<struct st_h2o_socket_t*>(
          malloc(sizeof(struct st_h2o_socket_t)));
  memset(sock, 0, sizeof(struct st_h2o_socket_t));
  h2o_accept(ctx, sock, NULL, NULL);
  free(ctx);
  free(sock);
  return 0;
}
```

The corrected code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_h2o_accept_ctx_t* ctx =
      static_cast<struct st_h2o_accept_ctx_t*>(
          malloc(sizeof(struct st_h2o_accept_ctx_t)));
  memset(ctx, 0, sizeof(struct st_h2o_accept_ctx_t));
  struct st_h2o_socket_t* sock =
      static_cast<struct st_h2o_socket_t*>(
          malloc(sizeof(struct st_h2o_socket_t)));
  memset(sock, 0, sizeof(struct st_h2o_socket_t));
  h2o_accept(ctx, sock, NULL, NULL);
  free(ctx);
  free(sock);