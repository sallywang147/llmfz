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
  fribidi_get_bidi_types (str, str_len, types);
  FriBidiLevel *levels = calloc (str_len, sizeof (FriBidiLevel));
  fribidi_get_par_embedding_levels_ex (types, NULL, str_len, NULL, levels);
  char *ar_props = calloc (str_len, sizeof (char));
  fribidi_join_arabic (types, str_len, levels, ar_props);
  free (types);
  free (levels);
  free (ar_props);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */