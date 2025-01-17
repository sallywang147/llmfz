#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fribidi.h>

extern "C" {
#include <fribidi-deprecated.h>
#include <fribidi-joining-types.h>
#include <fribidi-shape.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *)data;

  FriBidiLevel *levels = (FriBidiLevel *)calloc(str_len, sizeof(FriBidiLevel));
  FriBidiArabicProp *ar_props = (FriBidiArabicProp *)calloc(str_len, sizeof(FriBidiArabicProp));
  fribidi_get_par_embedding_levels(str, str_len, levels, &fribidi_par_embedding_levels_default);
  fribidi_join_arabic(str, str_len, levels, ar_props);
  fribidi_shape(FRIBIDI_FLAGS_DEFAULT, levels, str_len, ar_props, str);
  free(levels);
  free(ar_props);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */