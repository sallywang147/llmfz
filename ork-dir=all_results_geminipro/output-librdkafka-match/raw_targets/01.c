#include "rd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regexp.h"

int LLVMFuzzerTestOneInput(uint8_t *data, size_t size) {
  /* wrap random data in a null-terminated string */
  char *null_terminated = malloc(size + 1);
  memcpy(null_terminated, data, size);
  null_terminated[size] = '\0';

  const char *error;
  Reprog *p = re_regcomp(null_terminated, 0, &error);
  if (p == NULL) {
    /* compilation failed, skip this input */
    free(null_terminated);
    return 0;
  }

  Reinst *pc = re_regparse(p);
  if (pc == NULL) {
    /* parsing failed, skip this input */
    re_regfree(p);
    free(null_terminated);
    return 0;
  }

  /* allocate a Resub structure */
  Resub *out = (Resub *)malloc(sizeof(Resub) * p->re_nsub);
  if (out == NULL) {
    /* allocation failed, skip this input */
    re_regfree(p);
    free(null_terminated);
    return 0;
  }

  /* run the match */
  int ret = match(pc, null_terminated, null_terminated, 0, out);

  /* cleanup */
  free(out);
  re_regfree(p);
  free(null_terminated);

  return 0;
}

#if WITH_MAIN
#include "helpers.h"

int main(int argc, char **argv) {
  int i;
  for (i = 1; i < argc; i++) {
    size_t size;
    uint8_t *buf = read_file(argv[i], &size);
    LLVMFuzzerTestOneInput(buf, size);
    free(buf);
  }
}
#endif