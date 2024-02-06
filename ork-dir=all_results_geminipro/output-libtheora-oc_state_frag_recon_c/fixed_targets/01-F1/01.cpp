#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "oc_state.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct oc_theora_state state;
  size_t fragi = stream.ConsumeIntegral<size_t>();
  int pli = stream.ConsumeIntegral<int>();
  int last_zzi = stream.ConsumeIntegral<int>();
  short dc_quant = stream.ConsumeIntegral<short>();
  const size_t dct_coeffs_size = stream.ConsumeIntegral<size_t>();
  std::vector<short> dct_coeffs(dct_coeffs_size);
  stream.ConsumeBytes<short>(dct_coeffs.data(), dct_coeffs_size);

  oc_state_frag_recon_c(&state, fragi, pli, dct_coeffs.data(), last_zzi,
                        dc_quant);
  return 0;
}