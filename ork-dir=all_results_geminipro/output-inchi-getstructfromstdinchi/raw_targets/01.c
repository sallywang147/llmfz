#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "inchi_api.h"

// Define the maximum value for size_t. We return if the fuzzing input is equal
// to kSizeMax because appending the null-terminator to the InChI buffer would
// cause wraparound, thereby initializing the buffer to size 0.
static const size_t kSizeMax = (size_t)-1;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (size == kSizeMax)
    return 0;

  char *szINCHISource = malloc(sizeof(char) * (size + 1));
  memcpy(szINCHISource, data, size);
  szINCHISource[size] = '\0'; // InChI string must be null-terminated

  struct tagINCHI_InputINCHI inpInChI;
  inpInChI.szInChI = szINCHISource;
  inpInChI.szOptions = NULL;

  struct tagINCHI_OutputStruct outStruct;
  GetStructFromStdINCHI(&inpInChI, &outStruct);

  FreeStructFromINCHI(&outStruct);
  free(szINCHISource);

  return 0;
}