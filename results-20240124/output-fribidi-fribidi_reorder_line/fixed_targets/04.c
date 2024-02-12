#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <fribidi.h>

extern "C" {
#include <fribidi-bidi.h>
}

int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
{
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *) data;

  FriBidiCharType *types = (FriBidiCharType *) calloc (str_len, sizeof (FriBidiCharType));
  fribidi_get_bidi_types (str, str_len, types);
  FriBidiParType par_type = FRIBIDI_PAR_ON;
  FriBidiLevel level = fribidi_get_par_embedding_levels_ex (types, NULL, str_len, &par_type, NULL);
  if ((0)) assert (level);
  FriBidiLevel *levels = (FriBidiLevel *) calloc (str_len, sizeof (FriBidiLevel));
  fribidi_get_par_embedding_levels_ex (types, NULL, str_len, &par_type, levels);
  FriBidiStrIndex *visual_str = (FriBidiStrIndex *) calloc (str_len, sizeof (FriBidiStrIndex));
  int *map = (int *) calloc (str_len, sizeof (int));
  fribidi_reorder_line(str, types, str_len, 0, 0, *str, visual_str, map);
  free (types);
  free (levels);
  free (visual_str);
  free (map);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */