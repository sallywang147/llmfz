#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

extern "C" {
#include <fribidi.h>
}

int LLVMFuzzerTestOneInput (const uint8_t *data, size_t size)
{
  const FriBidiStrIndex str_len = size / 4;
  FriBidiChar *str = (FriBidiChar *) data;

  FriBidiCharType *types = (FriBidiCharType *)calloc (str_len, sizeof (FriBidiCharType));
  FriBidiBracketType *btypes = (FriBidiBracketType *)calloc (str_len, sizeof (FriBidiBracketType));
  FriBidiLevel *levels = (FriBidiLevel *)calloc (str_len, sizeof (FriBidiLevel));
  fribidi_get_bidi_types (str, str_len, types);
  fribidi_get_bracket_types (str, str_len, types, btypes);
  FriBidiParType par_type = FRIBIDI_PAR_ON;
  FriBidiLevel level = fribidi_get_par_embedding_levels_ex (types, btypes, str_len, &par_type, levels);
  if ((0)) assert (level);
  int *visual_str = (int *)malloc (str_len * sizeof (FriBidiChar));
  int *positions_L_to_V = (int *)malloc (str_len * sizeof (FriBidiStrIndex));
  int *positions_V_to_L = (int *)malloc (str_len * sizeof (FriBidiStrIndex));
  fribidi_log2vis (str, str_len, 0, visual_str, positions_L_to_V, positions_V_to_L, NULL);
  free (types);
  free (btypes);
  free (levels);
  free (visual_str);
  free (positions_L_to_V);
  free (positions_V_to_L);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */