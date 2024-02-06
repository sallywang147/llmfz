#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "theora/theora.h"

extern "C" {
#include "theora/theoradec.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct oc_theora_state* state =
      static_cast<struct oc_theora_state*>(malloc(sizeof(struct oc_theora_state)));
  if (state == nullptr) {
    return 0;
  }
  const size_t fragindex = stream.ConsumeIntegral<size_t>();
  const int pli = stream.ConsumeIntegral<int>();
  const int last_zzi = stream.ConsumeIntegral<int>();
  const short dc_quant = stream.ConsumeIntegral<short>();
  const size_t dct_coeffs_size = stream.ConsumeIntegralInRange<size_t>(
      0, 1 << 20);
  std::vector<short> dct_coeffs(dct_coeffs_size);
  stream.ConsumeBytes<short>(dct_coeffs.data(), dct_coeffs.size());

  oc_state_frag_recon_c(state, fragindex, pli, dct_coeffs.data(), last_zzi,
                         dc_quant);

  free(state);
  return 0;
}