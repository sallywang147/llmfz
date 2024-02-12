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
  FriBidiBracketType *btypes = calloc (str_len, sizeof (FriBidiBracketType));
  FriBidiLevel *levels = calloc (str_len, sizeof (FriBidiLevel));
  FriBidiCharType *ar_props = calloc (str_len, sizeof (FriBidiCharType));
  fribidi_get_bidi_types (str, str_len, types);
  fribidi_get_bracket_types (str, str_len, types, btypes);
  FriBidiParType par_type = FRIBIDI_PAR_ON;
  FriBidiLevel level = fribidi_get_par_embedding_levels_ex (types, btypes, str_len, &par_type, levels);
  if ((0)) assert (level);
  fribidi_shape (FRIBIDI_FLAGS_DEFAULT, levels, str_len, ar_props, str);
  free (types);
  free (btypes);
  free (levels);
  free (ar_props);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */