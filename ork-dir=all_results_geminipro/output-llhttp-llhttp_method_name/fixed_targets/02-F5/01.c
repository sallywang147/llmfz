#include "llhttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <llhttp.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // We need one byte to determine the method name
  if (size < 1) {
    return 0;
  }

  // Get the method name
  int method = data[0];
  data += 1;
  size -= 1;

  // Call the function to fuzz
  const char *method_name = llhttp_method_name(method);

  // Use the result
  if (method_name != NULL) {
    printf("Method name: %s\n", method_name);
  }

  return 0;
}