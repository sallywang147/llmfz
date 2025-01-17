#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"
#include "tpm2_fuzz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  CreateLoaded_In in = {};
  CreateLoaded_Out out = {};

  in.parentHandle = provider.ConsumeIntegral<uint32_t>();
  in.inSensitive.sensitive.data = provider.ConsumeBytes<uint8_t>(
      provider.ConsumeIntegralInRange<uint32_t>(0, 1024));
  in.inSensitive.sensitive.size = in.inSensitive.sensitive.data.size();
  in.inPublic.publicArea.nameAlg =
      provider.ConsumeIntegralInRange<TPMI_ALG_HASH>(TPM2_ALG_FIRST, TPM2_ALG_LAST);
  in.inPublic.publicArea.type =
      provider.ConsumeIntegralInRange<TPMI_ALG_PUBLIC>(TPM2_ALG_FIRST, TPM2_ALG_LAST);
  in.inPublic.publicArea.parameters.rsaDetail.exponent =
      provider.ConsumeIntegralInRange<uint32_t>(0, 1024);
  in.inPublic.publicArea.parameters.rsaDetail.modulus.size =
      provider.ConsumeIntegralInRange<uint32_t>(0, 1024);
  in.inPublic.publicArea.parameters.rsaDetail.modulus.data =
      provider.ConsumeBytes<uint8_t>(in.inPublic.publicArea.parameters.rsaDetail.modulus.size);
  in.outsideInfo.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  in.outsideInfo.data = provider.ConsumeBytes<uint8_t>(in.outsideInfo.size);

  TPM2_CreateLoaded(&in, &out);

  return 0;
}