#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "Tpm.h"
#include "TpmTypes.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct CreatePrimary_In in;
  memset(&in, 0, sizeof(in));
  in.primaryHandle = stream.ConsumeIntegral<uint32_t>();
  in.inSensitive.sensitive.data.size = stream.ConsumeIntegral<uint16_t>();
  in.inSensitive.sensitive.data.buffer =
      stream.ConsumeBytes<uint8_t>(in.inSensitive.sensitive.data.size);
  in.inPublic.publicArea.type = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.nameAlg = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.objectAttributes.val =
      stream.ConsumeIntegral<uint32_t>();
  in.inPublic.publicArea.authPolicy.size = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.authPolicy.buffer =
      stream.ConsumeBytes<uint8_t>(in.inPublic.publicArea.authPolicy.size);
  in.inPublic.publicArea.parameters.rsaDetail.symmetric.algorithm =
      stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.parameters.rsaDetail.symmetric.keyBits.size =
      stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.parameters.rsaDetail.symmetric.keyBits.buffer =
      stream.ConsumeBytes<uint8_t>(
          in.inPublic.publicArea.parameters.rsaDetail.symmetric.keyBits.size);
  in.inPublic.publicArea.parameters.rsaDetail.scheme.scheme =
      stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.parameters.rsaDetail.scheme.details.oaep.hashAlg =
      stream.ConsumeIntegral<uint16_t>();
  in.creationPCR.count = stream.ConsumeIntegral<uint32_t>();
  for (uint32_t i = 0; i < in.creationPCR.count; i++) {
    in.creationPCR.pcrSelection[i].hash = stream.ConsumeIntegral<uint8_t>();
    in.creationPCR.pcrSelection[i].sizeofSelect =
        stream.ConsumeIntegral<uint8_t>();
    in.creationPCR.pcrSelection[i].pcrSelect =
        stream.ConsumeBytes<uint8_t>(in.creationPCR.pcrSelection[i].sizeofSelect);
  }

  struct CreatePrimary_Out out;
  memset(&out, 0, sizeof(out));

  int ret = TPM2_CreatePrimary(&in, &out);
  if (ret != TPM_RC_SUCCESS) {
    return 0;
  }

  return 0;
}