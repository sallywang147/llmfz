 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "http_parser.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
  if (size == 0) {
    return 0;
  }
  // This is a fuzzer for http_errno_name, which takes an int as input
  // and returns a string containing the name of the error.
  // We can fuzz this function by passing in a random int and checking
  // that the returned string is valid.
  int errnum = *(int*)data;
  char *errname = http_errno_name(errnum);

  // Check that the returned string is valid.
  if (errname == NULL) {
    return 0;
  }

  // Check that the returned string is not empty.
  if (strlen(errname) == 0) {
    return 0;
  }

  // Check that the returned string does not contain any invalid characters.
  for (size_t i = 0; i < strlen(errname); i++) {
    if (!isalnum(errname[i]) && errname[i] != '_') {
      return 0;
    }
  }

  return 0;
}