#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "INCHI-API.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the input and output structures
  tagINCHI_InputINCHI inpInChI;
  inpInChI.szInChI = stream.ConsumeRandomLengthString().c_str();
  inpInChI.szOptions = stream.ConsumeRandomLengthString().c_str();

  tagINCHI_OutputStruct outStruct;

  // Call the function with the initialized parameters
  GetStructFromStdINCHI(&inpInChI, &outStruct);

  // Free any memory allocated by the function
  FreeStructFromINCHI(&outStruct);

  return 0;
}