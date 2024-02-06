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
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (size == kSizeMax)
    return 0;

  char *szINCHISource = malloc(sizeof(char) * (size + 1));
  memcpy(szINCHISource, data, size);
  szINCHISource[size] = '\0'; // InChI string must be null-terminated

  // Buffer lengths taken from InChI API reference, located at
  // https://www.inchi-trust.org/download/104/InChI_API_Reference.pdf, page 24
  char szINCHIKey[28], szXtra1[65], szXtra2[65];
  struct inchi_InputEx inp;
  struct tagINCHI_Output out;

  inp.szInChI = szINCHISource;
  inp.szOptions = NULL;
  inp.bChiralFlag = 0;
  inp.bTautFlag = 0;
  inp.bNoStructFlag = 0;
  inp.bNoIsotopicFlag = 0;
  inp.bRelativeStereoFlag = 0;
  inp.bReverseStereoFlag = 0;
  inp.bAuxInfoFlag = 0;
  inp.nMode = 0;
  inp.bPubChemXMLFlag = 0;
  inp.bStereochemistryFlag = 0;
  inp.bRectifyFlag = 0;
  inp.bDoNotAddHFlag = 0;
  inp.bSkipNormalization = 0;
  inp.bNoImplicitHydrogens = 0;
  inp.bFixedHFlag = 0;
  inp.bKekuleFlag = 0;
  inp.bCanonSmilesFlag = 0;

  GetINCHIEx(&inp, &out);

  free(szINCHISource);
  FreeINCHI(&out);

  return 0;
}
}
```

The following changes were made to the code:

- The `bChiralFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bTautFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bNoStructFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bNoIsotopicFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bRelativeStereoFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bReverseStereoFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bAuxInfoFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `nMode` field in the `inchi_InputEx` struct was initialized to 0.
- The `bPubChemXMLFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bStereochemistryFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bRectifyFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bDoNotAddHFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bSkipNormalization` field in the `inchi_InputEx` struct was initialized to 0.
- The `bNoImplicitHydrogens` field in the `inchi_InputEx` struct was initialized to 0.
- The `bFixedHFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bKekuleFlag` field in the `inchi_InputEx` struct was initialized to 0.
- The `bCanonSmilesFlag` field in the `inchi_InputEx` struct was initialized to 0.