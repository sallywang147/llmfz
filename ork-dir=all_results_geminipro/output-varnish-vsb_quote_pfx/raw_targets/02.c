#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache/cache_esi.h"
#include "cache/cache_filter.h" /* struct vfp_ctx */
#include "cache/cache_varnishd.h"
#include "cache/cache_vgz.h" /* enum vgz_flag */

#include "vfil.h"

int LLVMFuzzerTestOneInput(const uint8_t *, size_t);

struct VSC_main *VSC_C_main;
volatile struct params *cache_param;

int PAN__DumpStruct(struct vsb *vsb, int block, int track, const void *ptr, const char *smagic, unsigned magic, const char *fmt, ...) {
  (void)vsb;
  (void)block;
  (void)track;
  (void)ptr;
  (void)smagic;
  (void)magic;
  (void)fmt;
  return (0);
}

void VSL(enum VSL_tag_e tag, vxid_t vxid, const char *fmt, ...) {
  (void)tag;
  (void)vxid;
  (void)fmt;
}

void VSLb(struct vsl_log *vsl, enum VSL_tag_e tag, const char *fmt, ...) {
  (void)vsl;
  (void)tag;
  (void)fmt;
}

void VSLb_ts(struct vsl_log *l, const char *event, vtim_real first, vtim_real *pprev, vtim_real now) {
  (void)l;
  (void)event;
  (void)first;
  (void)pprev;
  (void)now;
}

void WRK_Log(enum VSL_tag_e tag, const char *fmt, ...) {

  (void)tag;
  (void)fmt;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct VSC_main __VSC_C_main;
  struct params __cache_param;
  struct http req[1];
  struct http resp[1];
  struct vfp_ctx vc[1];
  struct worker wrk[1];
  struct ws ws[1];
  struct vep_state *vep;
  struct vsb *vsb;
  txt hd[HTTP_HDR_URL + 1];
  char ws_buf[1024];
  char *pfx;
  char *v;
  int len;
  int how;

  if (size < 1)
    return (0);

  AN(data);

  VSC_C_main = &__VSC_C_main;
  cache_param = &__cache_param;

  memset(&__cache_param, 0, sizeof(__cache_param));
#define BSET(b, no) (b)[(no) >> 3] |= (0x80 >> ((no) & 7))
  if (data[0] & 0x8f)
    BSET(__cache_param.feature_bits, FEATURE_ESI_IGNORE_HTTPS);
  if (size > 1 && data[1] & 0x8f)
    BSET(__cache_param.feature_bits, FEATURE_ESI_DISABLE_XML_CHECK);
  if (size > 2 && data[2] & 0x8f)
    BSET(__cache_param.feature_bits, FEATURE_ESI_IGNORE_OTHER_ELEMENTS);
  if (size > 3 && data[3] & 0x8f)
    BSET(__cache_param.feature_bits, FEATURE_ESI_REMOVE_BOM);
#undef BSET

  /* Setup ws */
  WS_Init(ws, "req", ws_buf, sizeof ws_buf);

  /* Setup req */
  INIT_OBJ(req, HTTP_MAGIC);
  req->hd = hd;
  req->hd[HTTP_HDR_URL].b = "/";
  req->ws = ws;

  /* Setup resp */
  INIT_OBJ(resp, HTTP_MAGIC);
  resp->ws = ws;

  /* Setup wrk */
  INIT_OBJ(wrk, WORKER_MAGIC);

  /* Setup vc */
  INIT_OBJ(vc, VFP_CTX_MAGIC);
  vc->wrk = wrk;
  vc->resp = resp;

  vep = VEP_Init(vc, req, NULL, NULL);
  AN(vep);
  VEP_Parse(vep, (const char *)data, size);
  vsb = VEP_Finish(vep);
  if (vsb != NULL)
    VSB_destroy(&vsb);
  WS_Rollback(ws, 0);

  pfx = (char *)data;
  v = (char *)data;
  len = size;
  how = 0;
  VSB_quote_pfx(vsb, pfx, v, len, how);

  return (0);
}

#if defined(TEST_DRIVER)
int main(int argc, char **argv) {
  ssize_t len;
  char *buf;
  int i;

  for (i = 1; i < argc; i++) {
    len = 0;
    buf = VFIL_readfile(NULL, argv[i], &len);
    AN(buf);
    LLVMFuzzerTestOneInput((uint8_t *)buf, len);
    free(buf);
  }
}
#endif