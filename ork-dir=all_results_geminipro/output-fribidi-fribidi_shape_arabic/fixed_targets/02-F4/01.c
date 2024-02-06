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
  FriBidiBracketType *btypes = calloc(str_len, sizeof(FriBidiBracketType));
  FriBidiLevel *levels = calloc(str_len, sizeof(FriBidiLevel));
  fribidi_get_bidi_types(str, str_len, types);
  fribidi_get_bracket_types(str, str_len, types, btypes);
  FriBidiParType par_type = FRIBIDI_PAR_ON;
  FriBidiLevel level = fribidi_get_par_embedding_levels_ex(types, btypes, str_len, &par_type, levels);
  if (level == 0)
    assert(0);

  char *ar_props = calloc(str_len, sizeof(char));
  fribidi_get_arabic_properties(str, str_len, levels, ar_props);

  fribidi_shape_arabic(0, levels, str_len, ar_props, str);

  free(types);
  free(btypes);
  free(levels);
  free(ar_props);
  return 0;
}