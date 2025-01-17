#include <tpm2.h>
#include <cstdio>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  TPM2B_SENSITIVE_CREATE inSensitive = {0};
  TPM2B_PUBLIC inPublic = {0};
  TPM2B_DATA outsideInfo = {0};
  TPML_PCR_SELECTION creationPCR = {0};
  TPM2B_NAME name = {0};
  TPM2B_PUBLIC outPublic = {0};
  TPM2B_CREATION_DATA creationData = {0};
  TPM2B_DIGEST creationHash = {0};
  TPMT_TK_CREATION creationTicket = {0};
  TPM2B_PRIVATE outPrivate = {0};

  inSensitive.size = 0;
  inPublic.size = 0;
  outsideInfo.size = 0;
  creationPCR.count = 0;
  name.size = 0;
  outPublic.size = 0;
  creationData.size = 0;
  creationHash.size = 0;
  creationTicket.tag = TPM2_ST_CREATION;
  creationTicket.hierarchy = TPM2_RH_OWNER;
  outPrivate.size = 0;

  TPM2_CreatePrimary(
      (TPM2_CreatePrimary_In *) &inSensitive,
      (TPM2_CreatePrimary_Out *) &outPublic,
      &creationData,
      &creationHash,
      &creationTicket,
      &outPrivate,
      &name,
      &creationPCR,
      &outsideInfo);

  return 0;
}