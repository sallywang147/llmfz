#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "inchi_api.h"
}

// Define the maximum value for size_t. We return if the fuzzing input is equal
// to kSizeMax because appending the null-terminator to the InChI string would
// cause wraparound, thereby initializing the buffer to size 0.
static const size_t kSizeMax = (size_t)-1;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (size == kSizeMax)
    return 0;

  char *szINCHISource = malloc(sizeof(char) * (size + 1));
  memcpy(szINCHISource, data, size);
  szINCHISource[size] = '\0'; // InChI string must be null-terminated

  struct tagINCHI_Input inp;
  inp.szInChI = szINCHISource;
  inp.szOptions = NULL;

  struct tagINCHI_Output out;
  GetStdINCHI(&inp, &out);

  FreeINCHI(&out);
  free(szINCHISource);

  return 0;
}