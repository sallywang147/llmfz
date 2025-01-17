#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" {
#include "nghttp2_session.h"
#include "nghttp2_frame.h"
#include "nghttp2_hd.h"
#include <string.h>

#include "nghttp2_test_helper.h"

#define HEADERS_LENGTH 7

static nghttp2_nv fuzz_make_nv(std::string s1, std::string s2) {
  nghttp2_nv nv;
  uint8_t *n = (uint8_t *)malloc(s1.size());
  memcpy(n, s1.c_str(), s1.size());

  uint8_t *v = (uint8_t *)malloc(s2.size());
  memcpy(v, s2.c_str(), s2.size());

  nv.name = n;
  nv.value = v;
  nv.namelen = s1.size();
  nv.valuelen = s2.size();
  nv.flags = NGHTTP2_NV_FLAG_NONE;

  return nv;
}

static void fuzz_free_nv(nghttp2_nv *nv) {
  free(nv->name);
  free(nv->value);
}

void check_session_recv(FuzzedDataProvider *data_provider) {
  nghttp2_session *session;
  nghttp2_mem *mem;
  int rv;
  nghttp2_frame frame;
  nghttp2_bufs bufs;

  mem = nghttp2_mem_default();
  frame_pack_bufs_init(&bufs);

  /* Create a set of headers seeded with data from the fuzzer */
  nghttp2_nv *nva = (nghttp2_nv *)mem->malloc(sizeof(nghttp2_nv) * HEADERS_LENGTH, NULL);
  for (int i = 0; i < HEADERS_LENGTH; i++) {
    nva[i] = fuzz_make_nv(data_provider->ConsumeRandomLengthString(30), data_provider->ConsumeRandomLengthString(300));
  }

  /* Perform a set of operations with the fuzz data */
  nghttp2_frame_headers_init(&frame, NGHTTP2_FLAG_END_STREAM | NGHTTP2_FLAG_END_HEADERS, 1000000007, NGHTTP2_HCAT_REQUEST, NULL, nva, HEADERS_LENGTH);

  rv = nghttp2_frame_pack_headers(&bufs, &frame, NULL);
  if (rv == 0) {
    session = nghttp2_session_new(mem, NULL, NULL);
    nghttp2_session_recv(session, &bufs);
    nghttp2_session_del(session);
  }

  nghttp2_nv *nva2 = NULL;
  rv = nghttp2_nv_array_copy(&nva2, nva, HEADERS_LENGTH, mem);
  if (rv == 0) {
    nghttp2_nv_array_del(nva2, mem);
  }

  /* Cleanup */
  for (int i = 0; i < HEADERS_LENGTH; i++) {
    fuzz_free_nv(&nva[i]);
  }

  nghttp2_bufs_free(&bufs);
  nghttp2_frame_headers_free(&frame, mem);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider data_provider(data, size);

  check_session_recv(&data_provider);
  return 0;
}

} // extern C