#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "inchi_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct inchi_InputEx inp;
  struct tagINCHI_Output out;

  inp.szOptions = stream.ConsumeRandomLengthString().c_str();
  
  inp.num_atoms = stream.ConsumeIntegralInRange<int>(0, 100);
  inp.atom = (inchi_Atom*)calloc(inp.num_atoms, sizeof(inchi_Atom));
  for (int i = 0; i < inp.num_atoms; i++) {
    inp.atom[i].x = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].y = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].z = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].num_bonds = stream.ConsumeIntegralInRange<int>(0, 4);
    for (int j = 0; j < inp.atom[i].num_bonds; j++) {
      inp.atom[i].neighbor[j] = stream.ConsumeIntegralInRange<int>(0, inp.num_atoms - 1);
      inp.atom[i].bond_type[j] = stream.ConsumeIntegralInRange<int>(1, 4);
    }
  }

  GetINCHIEx(&inp, &out);

  free(inp.atom);

  return 0;
}