#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "inchi_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize INCHI_Input
  tagINCHI_Input inp;
  inp.szOptions = stream.ConsumeRandomLengthString().c_str();
  inp.num_atoms = stream.ConsumeIntegralInRange<int>(0, 100);
  inp.num_stereo0D = stream.ConsumeIntegralInRange<int>(0, 100);

  // Initialize atoms array
  inp.atom = (inchi_Atom *) calloc(inp.num_atoms, sizeof(inchi_Atom));
  for (int i = 0; i < inp.num_atoms; i++) {
    inp.atom[i].x = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].y = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].z = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].num_bonds = stream.ConsumeIntegralInRange<int>(0, 20);
    // Initialize other atom fields as needed
  }

  // Initialize INCHI_Output
  tagINCHI_Output out;
  out.szInChI = NULL;
  out.szAuxInfo = NULL;
  out.szMessage = NULL;
  out.szLog = NULL;

  // Call the target function
  int ret = GetStdINCHI(&inp, &out);

  // Free allocated memory
  free(inp.atom);
  FreeStdINCHI(&out);

  return 0;
}