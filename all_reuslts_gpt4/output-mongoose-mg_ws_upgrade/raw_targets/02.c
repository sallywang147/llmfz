#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mongoose.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct mg_mgr mgr;
  struct mg_connection *nc;
  struct mg_http_message *hm;
  char *fmt;

  mg_mgr_init(&mgr, NULL);
  nc = mg_mk_conn(&mgr);
  hm = (struct mg_http_message *) calloc(1, sizeof(struct mg_http_message));
  fmt = (char *) malloc(stream.remaining_bytes() + 1);

  if (nc == NULL || hm == NULL || fmt == NULL) {
    free(hm);
    free(fmt);
    mg_mgr_free(&mgr);
    return 0;
  }

  std::string str = stream.ConsumeRemainingBytesAsString();
  memcpy(fmt, str.c_str(), str.size());
  fmt[str.size()] = '\0';

  mg_ws_upgrade(nc, hm, fmt);

  free(hm);
  free(fmt);
  mg_mgr_free(&mgr);

  return 0;
}