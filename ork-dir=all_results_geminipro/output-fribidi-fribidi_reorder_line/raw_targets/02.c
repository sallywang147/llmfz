#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fribidi.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *)data;

  FriBidiCharType *types = calloc(str_len, sizeof(FriBidiCharType));
  FriBidiLevel *levels = calloc(str_len, sizeof(FriBidiLevel));
  fribidi_get_bidi_types(str, str_len, types);
  FriBidiParType par_type = FRIBIDI_PAR_ON;
  fribidi_get_par_embedding_levels_ex(types, NULL, str_len, &par_type, levels);

  int *visual_str = calloc(str_len, sizeof(int));
  int *map = calloc(str_len, sizeof(int));
  char ret = fribidi_reorder_line(0, types, str_len, 0, par_type, levels, visual_str, map);
  if ((0))
    assert(ret);
  free(types);
  free(levels);
  free(visual_str);
  free(map);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */