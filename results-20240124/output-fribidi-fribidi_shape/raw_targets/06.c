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
  FriBidiArabicShaping *ar_props = calloc (str_len, sizeof (FriBidiArabicShaping));
  fribidi_get_par_embedding_levels (str, str_len, levels);
  fribidi_get_arabic_shaping (str, str_len, levels, ar_props);
  fribidi_shape (FRIBIDI_FLAGS_DEFAULT, (char *) levels, str_len, (char *) ar_props, str);
  free (levels);
  free (ar_props);
  return 0;
}

/* Editor directions:
 * vim:textwidth=78:tabstop=8:shiftwidth=2:autoindent:cindent
 */