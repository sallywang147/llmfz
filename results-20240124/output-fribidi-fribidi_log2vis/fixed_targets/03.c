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

  FriBidiLevel *levels = calloc (str_len, sizeof (FriBidiLevel));
  FriBidiParType par_type = FRIBIDI_PAR_ON;
  FriBidiLevel level = fribidi_get_par_embedding_levels_ex (NULL, NULL, str_len, &par_type, levels);
  if ((0)) assert (level);

  FriBidiCharType *types = calloc (str_len, sizeof (FriBidiCharType));
  fribidi_get_bidi_types (str, str_len, types);

  FriBidiChar *visual_str = calloc (str_len, sizeof (FriBidiChar));
  int *positions_L_to_V = calloc (str_len, sizeof (int));
  int *positions_V_to_L = calloc (str_len, sizeof (int));
  fribidi_log2vis (str, str_len, &par_type, visual_str, positions_L_to_V, positions_V_to_L, levels);

  free (types);
  free (levels);
  free (visual_str);
  free (positions_L_to_V);
  free (positions_V_to_L);

  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */