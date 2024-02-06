#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fribidi.h>

extern "C" {
#include <fribidi.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *)data;

  FriBidiCharType *types = calloc(str_len, sizeof(FriBidiCharType));
  fribidi_get_bidi_types(str, str_len, types);
  char *embedding_levels = calloc(str_len, sizeof(char));
  char *ar_props = calloc(str_len, sizeof(char));
  fribidi_join_arabic(types, str_len, embedding_levels, ar_props);
  if ((0))
    assert(0);
  free(types);
  free(embedding_levels);
  free(ar_props);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */