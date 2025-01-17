#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fribidi.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *)data;

  FriBidiCharType *types = calloc(str_len, sizeof(FriBidiCharType));
  fribidi_get_bidi_types(str, str_len, types);
  FriBidiLevel *levels = calloc(str_len, sizeof(FriBidiLevel));
  FriBidiParType par_type = FRIBIDI_PAR_ON;
  fribidi_get_par_embedding_levels_ex(types, NULL, str_len, &par_type, levels);
  char *ar_props = calloc(str_len, sizeof(char));
  fribidi_get_arabic_properties(str, str_len, levels, ar_props);

  fribidi_shape_arabic(0, (char *)levels, str_len, ar_props, (int *)str);

  free(types);
  free(levels);
  free(ar_props);
  return 0;
}