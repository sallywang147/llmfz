 #include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer.h"
#include "gnutls/gnutls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  gnutls_session_t session;
  gnutls_datum_t in = {0};
  gnutls_datum_t out = {0};
  size_t out_size = 0;
  int ret;

  gnutls_global_init();
  gnutls_init(&session, GNUTLS_CLIENT);
  gnutls_set_default_priority(session);

  in.data = (unsigned char*)data;
  in.size = size;

  ret = gnutls_session_set_data(session, &in);
  if (ret < 0) {
    goto end;
  }

  ret = gnutls_session_get_data(session, NULL, &out_size);
  if (ret < 0) {
    goto end;
  }

  out.data = (unsigned char*)malloc(out_size);
  if (out.data == NULL) {
    goto end;
  }
  out.size = out_size;

  ret = gnutls_session_get_data(session, out.data, &out_size);
  if (ret < 0) {
    goto end;
  }

end:
  gnutls_deinit(session);
  gnutls_global_deinit();
  free(out.data);
  return 0;
}