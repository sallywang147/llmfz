#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tpm2_fuzz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  TPM2B_SENSITIVE_CREATE inSensitive = {0};
  inSensitive.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  provider.ConsumeBytes(inSensitive.sensitive, inSensitive.size);

  TPM2B_PUBLIC inPublic = {0};
  inPublic.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  provider.ConsumeBytes(inPublic.publicArea, inPublic.size);

  TPM2B_DATA outsideInfo = {0};
  outsideInfo.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  provider.ConsumeBytes(outsideInfo.buffer, outsideInfo.size);

  TPML_PCR_SELECTION creationPCR = {0};
  creationPCR.count = provider.ConsumeIntegralInRange<uint32_t>(0, 1024);
  for (size_t i = 0; i < creationPCR.count; i++) {
    creationPCR.pcrSelections[i].hash = provider.ConsumeIntegralInRange<TPM2_ALG_ID>(0, 1024);
    creationPCR.pcrSelections[i].sizeofSelect = provider.ConsumeIntegralInRange<uint8_t>(0, 1024);
    provider.ConsumeBytes(creationPCR.pcrSelections[i].pcrSelect, creationPCR.pcrSelections[i].sizeofSelect);
  }

  TPM2B_CREATION_DATA creationData = {0};
  creationData.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  provider.ConsumeBytes(creationData.buffer, creationData.size);

  TPM2B_DIGEST creationHash = {0};
  creationHash.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  provider.ConsumeBytes(creationHash.buffer, creationHash.size);

  TPMT_TK_CREATION creationTicket = {0};
  creationTicket.tag = provider.ConsumeIntegralInRange<TPM2_ST>(0, 1024);
  creationTicket.hierarchy = provider.ConsumeIntegralInRange<TPMI_RH_HIERARCHY>(0, 1024);
  creationTicket.digest.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  provider.ConsumeBytes(creationTicket.digest.buffer, creationTicket.digest.size);

  TPM2B_NAME name = {0};
  name.size = provider.ConsumeIntegralInRange<uint16_t>(0, 1024);
  provider.ConsumeBytes(name.name, name.size);

  TPM2B_PUBLIC outPublic = {0};
  TPM2B_CREATION_DATA outCreationData = {0};
  TPM2B_DIGEST outCreationHash = {0};
  TPMT_TK_CREATION outCreationTicket = {0};

  CreatePrimary_In in = {0};
  in.sensitive = &inSensitive;
  in.public = &inPublic;
  in.outsideInfo = &outsideInfo;
  in.creationPCR = &creationPCR;

  CreatePrimary_Out out = {0};
  out.public = &outPublic;
  out.creationData = &outCreationData;
  out.creationHash = &outCreationHash;
  out.creationTicket = &outCreationTicket;

  TPM2_CreatePrimary(&in, &out);

  return 0;
}