#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "inchi_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tagINCHI_InputINCHI inpInChI;
  tagINCHI_OutputStruct outStruct;

  // Initialize INCHI_InputINCHI struct
  inpInChI.szInChI = stream.ConsumeRandomLengthString().c_str();
  inpInChI.szOptions = stream.ConsumeRandomLengthString().c_str();

  // Call the target function
  int ret = GetStructFromStdINCHI(&inpInChI, &outStruct);

  // Free the allocated memory
  FreeStructFromINCHI(&outStruct);

  return 0;
}