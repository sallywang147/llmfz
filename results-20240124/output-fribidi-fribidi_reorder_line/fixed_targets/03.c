 #include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fribidi.h>

int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
{
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *) data;

  FriBidiCharType *types = calloc (str_len, sizeof (FriBidiCharType));
  FriBidiLevel *levels = calloc (str_len, sizeof (FriBidiLevel));
  fribidi_get_bidi_types (str, str_len, types);
  fribidi_get_par_embedding_levels_ex (types, NULL, str_len, NULL, levels);
  int *visual_str = calloc (str_len, sizeof (int));
  int *map = calloc (str_len, sizeof (int));
  fribidi_reorder_line (FRIBIDI_FLAGS_DEFAULT, types, str_len, 0, 0, levels, visual_str, map);
  if ((0)) assert (visual_str);
  free (types);
  free (levels);
  free (visual_str);
  free (map);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */