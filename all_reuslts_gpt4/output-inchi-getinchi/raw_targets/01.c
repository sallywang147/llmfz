#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "inchi_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tagINCHI_Input inp;
  inp.szOptions = nullptr;
  inp.num_atoms = stream.ConsumeIntegralInRange<int>(0, 100);
  inp.atom = (inchi_Atom*)calloc(inp.num_atoms, sizeof(inchi_Atom));
  if (!inp.atom) {
    return 0;
  }

  for (int i = 0; i < inp.num_atoms; ++i) {
    inp.atom[i].x = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].y = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].z = stream.ConsumeFloatingPoint<double>();
    inp.atom[i].num_bonds = stream.ConsumeIntegralInRange<int>(0, 20);
    for (int j = 0; j < inp.atom[i].num_bonds; ++j) {
      inp.atom[i].neighbor[j] = stream.ConsumeIntegralInRange<int>(0, inp.num_atoms - 1);
      inp.atom[i].bond_type[j] = stream.ConsumeIntegralInRange<int>(1, 3);
    }
  }

  tagINCHI_Output out;
  out.szInChI = nullptr;
  out.szAuxInfo = nullptr;
  out.szMessage = nullptr;
  out.szLog = nullptr;

  GetINCHI(&inp, &out);

  free(inp.atom);
  FreeINCHI(&out);

  return 0;
}