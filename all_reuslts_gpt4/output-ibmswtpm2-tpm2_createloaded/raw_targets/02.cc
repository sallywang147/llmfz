#include <stdint.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>
#include "TpmBuildSwitches.h"
#include "CreateLoaded_fp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create and initialize the input struct
  struct CreateLoaded_In in;
  in.parentHandle = stream.ConsumeIntegral<TPMI_DH_OBJECT>();
  in.inPublic.publicArea.type = stream.ConsumeIntegral<TPMI_ALG_PUBLIC>();
  in.inPublic.publicArea.nameAlg = stream.ConsumeIntegral<TPMI_ALG_HASH>();
  in.inPublic.publicArea.objectAttributes = stream.ConsumeIntegral<TPMA_OBJECT>();
  in.inPublic.publicArea.authPolicy = stream.ConsumeBytes<TPM2B_DIGEST>(stream.remaining_bytes() / 2);
  in.inPublic.publicArea.parameters.rsaDetail.symmetric.algorithm = stream.ConsumeIntegral<TPMI_ALG_SYM_OBJECT>();
  in.inPublic.publicArea.unique.rsa = stream.ConsumeBytes<TPM2B_PUBLIC_KEY_RSA>(stream.remaining_bytes());

  // Create the output struct
  struct CreateLoaded_Out out;

  // Call the function to fuzz
  TPM2_CreateLoaded(&in, &out);

  return 0;
}