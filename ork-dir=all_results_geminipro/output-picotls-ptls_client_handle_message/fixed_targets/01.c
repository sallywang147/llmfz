#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>

extern "C" {
#include "ptls/ptls.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct st_ptls_t *tls = NULL;
  struct st_ptls_buffer_t sendbuf;
  size_t epoch_offsets[16];
  size_t in_epoch = 0;
  struct st_ptls_handshake_properties_t properties;

  ptls_init(NULL, NULL);
  ptls_set_log_level(0);

  ptls_create(&tls, PTLS_CLIENT);
  ptls_buffer_init(&sendbuf, 4096);
  ptls_handshake_properties_init(&properties);

  ptls_client_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, (char *)data, size, &properties);

  ptls_buffer_dispose(&sendbuf);
  ptls_handshake_properties_free(&properties);
  ptls_free(tls);
  ptls_cleanup();

  return 0;
}
```

The issue is that the `ptls_client_handle_message` function is declared as `int ptls_client_handle_message(struct st_ptls_t *tls, struct st_ptls_buffer_t *sendbuf, size_t *epoch_offsets, size_t in_epoch, const unsigned char *message, size_t message_size, struct st_ptls_handshake_properties_t *properties)`, but it is called with `char *` instead of `unsigned char *`. This can be fixed by changing the type of the `message` parameter to `unsigned char *`.

The corrected code:
```c++
#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>

extern "C" {
#include "ptls/ptls.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct st_ptls_t *tls = NULL;
  struct st_ptls_buffer_t sendbuf;
  size_t epoch_offsets[16];
  size_t in_epoch = 0;
  struct st_ptls_handshake_properties_t properties;

  ptls_init(NULL, NULL);
  ptls_set_log_level(0);

  ptls_create(&tls, PTLS_CLIENT);
  ptls_buffer_init(&sendbuf, 4096);
  ptls_handshake_properties_init(&properties);

  ptls_client_handle_message(tls, &sendbuf, epoch_offsets, in_epoch, (const unsigned char *)data, size, &properties);

  ptls_buffer_dispose(&sendbuf);
  ptls_handshake_properties_free(&properties);
  ptls_free(tls);
  ptls_cleanup();

  return 0;
}