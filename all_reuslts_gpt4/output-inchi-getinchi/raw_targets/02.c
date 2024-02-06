#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "inchi_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tagINCHI_Input inp;
  tagINCHI_Output out;

  inp.szOptions = nullptr;

  // Extract the number of atoms
  inp.num_atoms = stream.ConsumeIntegralInRange<int>(0, 100);

  // Allocate memory for the atoms
  inp.atom = new INCHIAtom[inp.num_atoms];

  // Fill in the atoms
  for (int i = 0; i < inp.num_atoms; ++i) {
    inp.atom[i].x = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].y = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].z = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].num_bonds = stream.ConsumeIntegralInRange<int>(0, 4);
    inp.atom[i].charge = stream.ConsumeIntegralInRange<int>(-3, 3);
  }

  // Call the target function
  GetINCHI(&inp, &out);

  // Free the memory
  delete[] inp.atom;

  return 0;
}