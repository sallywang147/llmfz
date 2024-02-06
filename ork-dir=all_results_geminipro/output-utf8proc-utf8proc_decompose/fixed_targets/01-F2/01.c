#include <string.h>
#include <utf8proc.h>

extern "C" {
#include <stdlib.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1)
    return 0;

  /* Avoid timeout with long inputs */
  if (size > (64 * 1024))
    return 0;

  if (data[size - 1] != '\0')
    return 0;

  const uint8_t *ptr = data;
  utf8proc_int32_t c = 0, c_prev = 0, state = 0;
  utf8proc_option_t options;
  utf8proc_ssize_t ret, bytes = 0;
  size_t len = strlen((const char *)data);

  while (bytes != len) {
    ret = utf8proc_iterate(ptr, -1, &c);

    if (ret < 0 || ret == 0)
      break;

    bytes += ret;
    ptr += ret;

    utf8proc_tolower(c);
    utf8proc_toupper(c);
    utf8proc_totitle(c);
    utf8proc_islower(c);
    utf8proc_isupper(c);
    utf8proc_charwidth(c);
    utf8proc_category(c);
    utf8proc_category_string(c);
    utf8proc_codepoint_valid(c);

    utf8proc_grapheme_break(c_prev, c);
    utf8proc_grapheme_break_stateful(c_prev, c, &state);

    c_prev = c;
  }

  utf8proc_int32_t *copy = size >= 4 ? NULL : malloc(size);
  int *decomp = size >= 4 ? NULL : malloc(size);

  if (copy && decomp) {
    size /= 4;

    memcpy(copy, data, size);
    memcpy(decomp, data, size);
    utf8proc_decompose((char *)copy, size, decomp, size, UTF8PROC_COMPOSE);

    memcpy(copy, data, size);
    memcpy(decomp, data, size);
    utf8proc_decompose((char *)copy, size, decomp, size, UTF8PROC_DECOMPOSE);

    memcpy(copy, data, size);
    memcpy(decomp, data, size);
    utf8proc_decompose((char *)copy, size, decomp, size, UTF8PROC_NFC);

    memcpy(copy, data, size);
    memcpy(decomp, data, size);
    utf8proc_decompose((char *)copy, size, decomp, size, UTF8PROC_NFKC);

    free(copy);
    free(decomp);
  }

  free((void *)utf8proc_NFD(data));
  free((void *)utf8proc_NFC(data));
  free((void *)utf8proc_NFKD(data));
  free((void *)utf8proc_NFKC(data));
  free((void *)utf8proc_NFKC_Casefold(data));

  return 0;
}