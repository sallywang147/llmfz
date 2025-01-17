#include "rd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regexp.h"

extern "C" {
#include "helpers.h"
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

  /* create a Resub object */
  Resub *sub = malloc(sizeof(Resub));
  sub->nsub = 0;
  sub->startp = NULL;
  sub->endp = NULL;

  /* run the regular expression */
  int ret = re_regexec(p, null_terminated, sub, 0);

  /* cleanup */
  free(null_terminated);
  re_regfree(p);
  free(sub);

  return 0;
}

#if WITH_MAIN
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