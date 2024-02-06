#include <fuzzer/FuzzedDataProvider.h>
#include <tss2/tss2_sys.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  TSS2_RC rc;
  TSS2_SYS_CONTEXT *sysContext;
  size_t contextSize = Tss2_Sys_GetContextSize(0);
  sysContext = (TSS2_SYS_CONTEXT *)calloc(1, contextSize);
  Tss2_Sys_Initialize(sysContext, contextSize, NULL, NULL);

  TPMI_DH_OBJECT parentHandle = stream.ConsumeIntegral<TPMI_DH_OBJECT>();
  TPM2B_SENSITIVE_CREATE inSensitive = {};
  TPM2B_PUBLIC inPublic = {};
  TPM2B_DIGEST outsideInfo = {};
  TPML_PCR_SELECTION creationPCR = {};
  TPM2B_PRIVATE outPrivate = {};
  TPM2B_PUBLIC outPublic = {};
  TPM2B_CREATION_DATA creationData = {};
  TPM2B_DIGEST creationHash = {};
  TPMT_TK_CREATION creationTicket = {};
  TSS2L_SYS_AUTH_COMMAND cmdAuthsArray = {};
  TSS2L_SYS_AUTH_RESPONSE rspAuthsArray = {};

  if (stream.remaining_bytes() > 0) {
    size_t inSensitiveSize = stream.ConsumeIntegralInRange<size_t>(0, sizeof(TPM2B_SENSITIVE_CREATE));
    memcpy(&inSensitive, stream.ConsumeBytes(inSensitiveSize).data(), inSensitiveSize);
  }

  if (stream.remaining_bytes() > 0) {
    size_t inPublicSize = stream.ConsumeIntegralInRange<size_t>(0, sizeof(TPM2B_PUBLIC));
    memcpy(&inPublic, stream.ConsumeBytes(inPublicSize).data(), inPublicSize);
  }

  if (stream.remaining_bytes() > 0) {
    size_t outsideInfoSize = stream.ConsumeIntegralInRange<size_t>(0, sizeof(TPM2B_DIGEST));
    memcpy(&outsideInfo, stream.ConsumeBytes(outsideInfoSize).data(), outsideInfoSize);
  }

  if (stream.remaining_bytes() > 0) {
    size_t creationPCRSize = stream.ConsumeIntegralInRange<size_t>(0, sizeof(TPML_PCR_SELECTION));
    memcpy(&creationPCR, stream.ConsumeBytes(creationPCRSize).data(), creationPCRSize);
  }

  if (stream.remaining_bytes() > 0) {
    size_t cmdAuthsArraySize = stream.ConsumeIntegralInRange<size_t>(0, sizeof(TSS2L_SYS_AUTH_COMMAND));
    memcpy(&cmdAuthsArray, stream.ConsumeBytes(cmdAuthsArraySize).data(), cmdAuthsArraySize);
  }

  Tss2_Sys_Create(sysContext, parentHandle, &cmdAuthsArray, &inSensitive, &inPublic, &outsideInfo, &creationPCR, &outPrivate, &outPublic, &creationData, &creationHash, &creationTicket, &rspAuthsArray);

  Tss2_Sys_Finalize(sysContext);
  free(sysContext);

  return 0;
}