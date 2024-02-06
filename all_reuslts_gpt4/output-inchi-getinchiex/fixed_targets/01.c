#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "inchi_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  inchi_InputEx inp;
  inp.szOptions = stream.ConsumeRandomLengthString().c_str();

  std::vector<inchi_Atom> atoms(stream.ConsumeIntegralInRange<size_t>(0, 100));
  for (size_t i = 0; i < atoms.size(); i++) {
    atoms[i].x = stream.ConsumeFloatingPoint<double>();
    atoms[i].y = stream.ConsumeFloatingPoint<double>();
    atoms[i].z = stream.ConsumeFloatingPoint<double>();
    atoms[i].neighbor[0] = stream.ConsumeIntegralInRange<AT_NUM>(0, atoms.size()-1);
    atoms[i].neighbor[1] = stream.ConsumeIntegralInRange<AT_NUM>(0, atoms.size()-1);
    atoms[i].neighbor[2] = stream.ConsumeIntegralInRange<AT_NUM>(0, atoms.size()-1);
    atoms[i].neighbor[3] = stream.ConsumeIntegralInRange<AT_NUM>(0, atoms.size()-1);
    atoms[i].orig_at_number = stream.ConsumeIntegralInRange<AT_NUM>(0, atoms.size()-1);
  }

  inp.atom = atoms.data();
  inp.num_atoms = atoms.size();

  tagINCHI_Output out;
  GetINCHIEx(&inp, &out);

  if (out.szInChI) {
    free(out.szInChI);
  }
  if (out.szAuxInfo) {
    free(out.szAuxInfo);
  }
  if (out.szMessage) {
    free(out.szMessage);
  }
  if (out.szLog) {
    free(out.szLog);
  }

  return 0;
}