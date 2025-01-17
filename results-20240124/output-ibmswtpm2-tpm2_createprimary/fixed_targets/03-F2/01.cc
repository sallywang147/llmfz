#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "TPM2_CreatePrimary.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  TPM2B_PUBLIC inPublic;
  inPublic.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.nameAlg, sizeof(inPublic.publicArea.nameAlg));
  inPublic.publicArea.type = provider.ConsumeIntegral<TPMI_ALG_PUBLIC>();
  inPublic.publicArea.parameters.RSA.sensitive.size = provider.ConsumeIntegral<uint32_t>();
  inPublic.publicArea.parameters.RSA.sensitive.exponent = provider.ConsumeIntegral<uint32_t>();
  inPublic.publicArea.parameters.RSA.sensitive.modulus.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.parameters.RSA.sensitive.modulus.buffer, sizeof(inPublic.publicArea.parameters.RSA.sensitive.modulus.buffer));
  inPublic.publicArea.parameters.RSA.sensitive.prime1.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.parameters.RSA.sensitive.prime1.buffer, sizeof(inPublic.publicArea.parameters.RSA.sensitive.prime1.buffer));
  inPublic.publicArea.parameters.RSA.sensitive.prime2.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.parameters.RSA.sensitive.prime2.buffer, sizeof(inPublic.publicArea.parameters.RSA.sensitive.prime2.buffer));
  inPublic.publicArea.parameters.RSA.sensitive.exponent1.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.parameters.RSA.sensitive.exponent1.buffer, sizeof(inPublic.publicArea.parameters.RSA.sensitive.exponent1.buffer));
  inPublic.publicArea.parameters.RSA.sensitive.exponent2.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.parameters.RSA.sensitive.exponent2.buffer, sizeof(inPublic.publicArea.parameters.RSA.sensitive.exponent2.buffer));
  inPublic.publicArea.parameters.RSA.sensitive.coefficient.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.parameters.RSA.sensitive.coefficient.buffer, sizeof(inPublic.publicArea.parameters.RSA.sensitive.coefficient.buffer));
  inPublic.publicArea.parameters.RSA.sensitive.privateExponent.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.parameters.RSA.sensitive.privateExponent.buffer, sizeof(inPublic.publicArea.parameters.RSA.sensitive.privateExponent.buffer));
  inPublic.publicArea.unique.RSA.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inPublic.publicArea.unique.RSA.buffer, sizeof(inPublic.publicArea.unique.RSA.buffer));

  TPM2B_SENSITIVE_CREATE inSensitive;
  inSensitive.size = provider.ConsumeIntegral<uint32_t>();
  inSensitive.sensitive.data.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inSensitive.sensitive.data.buffer, sizeof(inSensitive.sensitive.data.buffer));

  TPM2B_DATA inOutsideInfo;
  inOutsideInfo.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(inOutsideInfo.buffer, sizeof(inOutsideInfo.buffer));

  TPML_PCR_SELECTION inPCRSelection;
  inPCRSelection.count = provider.ConsumeIntegral<uint32_t>();
  for (size_t i = 0; i < inPCRSelection.count; i++) {
    inPCRSelection.pcrSelections[i].hash = provider.ConsumeIntegral<TPMI_ALG_HASH>();
    inPCRSelection.pcrSelections[i].sizeofSelect = provider.ConsumeIntegral<uint8_t>();
    provider.ConsumeBytes(inPCRSelection.pcrSelections[i].pcrSelect, sizeof(inPCRSelection.pcrSelections[i].pcrSelect));
  }

  TPM2B_PUBLIC_KEY_RSA outPublic;
  outPublic.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(outPublic.publicArea.nameAlg, sizeof(outPublic.publicArea.nameAlg));
  outPublic.publicArea.type = provider.ConsumeIntegral<TPMI_ALG_PUBLIC>();
  outPublic.publicArea.parameters.RSA.exponent = provider.ConsumeIntegral<uint32_t>();
  outPublic.publicArea.parameters.RSA.modulus.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(outPublic.publicArea.parameters.RSA.modulus.buffer, sizeof(outPublic.publicArea.parameters.RSA.modulus.buffer));

  TPM2B_CREATION_DATA outCreationData;
  outCreationData.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(outCreationData.creationData, sizeof(outCreationData.creationData));

  TPM2B_DIGEST outHash;
  outHash.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(outHash.buffer, sizeof(outHash.buffer));

  TPMT_TK_CREATION outTicket;
  outTicket.tag = provider.ConsumeIntegral<TPM2_ST>();
  outTicket.hierarchy = provider.ConsumeIntegral<TPMI_RH_HIERARCHY>();
  outTicket.digest.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(outTicket.digest.buffer, sizeof(outTicket.digest.buffer));

  TPM2B_NAME outName;
  outName.size = provider.ConsumeIntegral<uint32_t>();
  provider.ConsumeBytes(outName.name, sizeof(outName.name));

  TPM2_CreatePrimary(
      &inPublic,
      &inSensitive,
      &inOutsideInfo,
      &inPCRSelection,
      &outPublic,
      &outCreationData,
      &outHash,
      &outTicket,
      &outName);

  return 0;
}