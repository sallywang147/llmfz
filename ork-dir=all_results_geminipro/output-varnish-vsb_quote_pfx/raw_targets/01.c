#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache/cache_varnishd.h" /* struct vsb */
#include "cache/cache_esi.h" /* enum ESI_QUOTE_ */

int LLVMFuzzerTestOneInput(const uint8_t *, size_t);

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
  struct vsb vsb;
  char *pfx;
  char *v;
  int len;
  int how;

  if (size < 1)
    return (0);

  AN(data);

  memset(&vsb, 0, sizeof(vsb));

  /* Setup pfx */
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  char *ptr = str.c_str();
  pfx = ptr;

  /* Setup v */
  std::string str2 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, size));
  char *ptr2 = str2.c_str();
  v = ptr2;

  /* Setup len */
  len = stream.ConsumeIntegral<int>();

  /* Setup how */
  how = stream.ConsumeIntegral<int>();

  VSB_quote_pfx(&vsb, pfx, v, len, how);

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