#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <fribidi.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *)data;

  FriBidiCharType *types = calloc(str_len, sizeof(FriBidiCharType));
  FriBidiLevel *levels = calloc(str_len, sizeof(FriBidiLevel));
  fribidi_get_bidi_types(str, str_len, types);
  fribidi_get_par_embedding_levels_ex(types, NULL, str_len, NULL, levels);
  char *ar_props = calloc(str_len, sizeof(char));
  fribidi_get_arabic_shaping_properties(str, levels, str_len, ar_props);
  fribidi_shape(0, levels, str_len, ar_props, str);
  if ((0))
    assert(str);
  free(types);
  free(levels);
  free(ar_props);
  return 0;
}