#include "wc.h"
#include "wtf.h"
#include <gc.h>
#include <stdint.h>
#include <stdlib.h>

static void *die_oom(size_t bytes) {
  fprintf(stderr, "Out of memory: %lu bytes unavailable!\n", (unsigned long)bytes);
  exit(1);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  static int init_done = 0;

  if (!init_done) {
    setenv("GC_LARGE_ALLOC_WARN_INTERVAL", "30000", 1);
    GC_INIT();
#if (GC_VERSION_MAJOR > 7) || ((GC_VERSION_MAJOR == 7) && (GC_VERSION_MINOR >= 2))
    GC_set_oom_fn(die_oom);
#else
    GC_oom_fn = die_oom;
#endif
#ifdef USE_M17N
#ifdef USE_UNICODE
    wtf_init(WC_CES_UTF_8, WC_CES_UTF_8);
#else
    wtf_init(WC_CES_EUC_JP, WC_CES_EUC_JP);
#endif
#endif
    init_done = 1;
  }

  /* Assume the data format is:
   *   <str1> \0 <ces>
   */
  const uint8_t *str1, *p;
  str1 = data;
  p = memchr(str1, '\0', size);
  if (p == NULL)
    return 0;
  int ces = *(p + 1);

  Str s = Strnew_charp_n((char *)str1, p - str1);
  wc_conv_from_utf7(s, ces);
  Strfree(s);

  return 0;
}