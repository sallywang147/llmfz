#include <fuzzer/FuzzedDataProvider.h>

#include <stdint.h>
#include <stdlib.h>

#include "tss2_sys.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _TSS2_SYS_OPAQUE_CONTEXT_BLOB *sysContext = NULL;
  int parentHandle = stream.ConsumeIntegral<int>();
  struct TSS2L_SYS_AUTH_COMMAND *cmdAuthsArray = NULL;
  struct TPM2B_SENSITIVE_CREATE *inSensitive = NULL;
  struct TPM2B_PUBLIC *inPublic = NULL;
  struct TPM2B_DIGEST *outsideInfo = NULL;
  struct TPML_PCR_SELECTION *creationPCR = NULL;
  struct TPM2B_PRIVATE *outPrivate = NULL;
  struct TPM2B_PUBLIC *outPublic = NULL;
  struct TPM2B_CREATION_DATA *creationData = NULL;
  struct TPM2B_DIGEST *creationHash = NULL;
  struct TPMT_TK_CREATION *creationTicket = NULL;
  struct TSS2L_SYS_AUTH_RESPONSE *rspAuthsArray = NULL;

  Tss2_Sys_Create(sysContext, parentHandle, cmdAuthsArray, inSensitive, inPublic,
                  outsideInfo, creationPCR, outPrivate, outPublic, creationData,
                  creationHash, creationTicket, rspAuthsArray);

  return 0;
}