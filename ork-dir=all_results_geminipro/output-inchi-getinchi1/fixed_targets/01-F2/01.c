#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "inchi_api.h"

// Define the maximum value for size_t. We return if the fuzzing input is equal
// to kSizeMax because appending the null-terminator to the InChI buffer would
// cause wraparound, thereby initializing the buffer to size 0.
static const size_t kSizeMax = (size_t)-1;

extern "C" {
#include "inchi_api.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (size == kSizeMax)
    return 0;

  char *szINCHISource = malloc(sizeof(char) * (size + 1));
  memcpy(szINCHISource, data, size);
  szINCHISource[size] = '\0'; // InChI string must be null-terminated

  struct inchi_InputEx extended_input;
  extended_input.szInChI = szINCHISource;
  extended_input.szOptions = NULL;

  struct tagINCHI_Output out;
  int enforce_std_format = 0;

  int status = GetINCHI1(&extended_input, &out, enforce_std_format);

  if (status != INCHI_RET_SUCCESS) {
    // Handle the error
    fprintf(stderr, "Error: %s\n", inchi_RetErr(status));
  }

  FreeINCHI(&out);

  free(szINCHISource);

  return 0;
}