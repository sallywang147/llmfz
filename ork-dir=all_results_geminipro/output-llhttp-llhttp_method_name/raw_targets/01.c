#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  /* We need four bytes to determine variable parameters */
  if (size < 4) {
    return 0;
  }

  int method = data[0] % 9;
  data += 4;
  size -= 4;

  /* Call the function to fuzz */
  char *result = llhttp_method_name(method);

  /* Do something with the result */
  if (result != NULL) {
    printf("Method name: %s\n", result);
  }

  return 0;
}