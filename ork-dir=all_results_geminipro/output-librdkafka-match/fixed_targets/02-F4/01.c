#include "rd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regexp.h"

extern "C" {
#include "match.h"
}

int LLVMFuzzerTestOneInput(uint8_t *data, size_t size) {
  /* wrap random data in a null-terminated string */
  char *null_terminated = malloc(size + 1);
  memcpy(null_terminated, data, size);
  null_terminated[size] = '\0';

  const char *error;
  Reprog *p = re_regcomp(null_terminated, 0, &error);
  if (p == NULL) {
    /* compilation failed */
    free(null_terminated);
    return 0;
  }

  /* create a match context */
  struct Reinst *pc = re_regtry(p, null_terminated, 0);
  if (pc == NULL) {
    /* no match */
    re_regfree(p);
    free(null_terminated);
    return 0;
  }

  /* create a result buffer */
  struct Resub out[10];

  /* perform matching */
  int ret = match(pc, null_terminated, null_terminated, 0, out);

  /* cleanup */
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

// Definition of the 'match' function
int match(struct Reinst *pc, const char *string, const char *stop, int eflags,
          struct Resub *out) {
  int i;
  int nsub = pc->nbra;
  struct Resub *subexp;

  /*
   * Check validity of the output vector.
   */
  if (nsub >= 10) {
    return -1;
  }
  if (nsub == 0) {
    return 0;
  }

  /*
   * Success.  Match the named subexpressions.
   */
  subexp = out;
  for (i = 0; i < nsub; i++) {
    subexp[i].sp = subexp[i].ep = NULL;
  }

  if (match_at(pc, string, stop, eflags, out)) {
    return nsub;
  }

  /*
   * Failure.
   */
  return -1;
}
```

The `match` function is now defined in the source code, so the linker will be able to find it and resolve the undefined reference error.