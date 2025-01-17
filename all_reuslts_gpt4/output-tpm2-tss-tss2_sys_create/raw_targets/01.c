#include <fuzzer/FuzzedDataProvider.h>
#include <tss2/tss2_sys.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize TSS2 system context
  TSS2_RC rc;
  TSS2_SYS_CONTEXT *sysContext;
  size_t contextSize = Tss2_Sys_GetContextSize(0);
  sysContext = (TSS2_SYS_CONTEXT*)calloc(1, contextSize);
  Tss2_Sys_Initialize(sysContext, contextSize, NULL, NULL);

  // Initialize parameters
  int parentHandle = stream.ConsumeIntegral<int>();
  TSS2L_SYS_AUTH_COMMAND cmdAuthsArray;
  TPM2B_SENSITIVE_CREATE inSensitive;
  TPM2B_PUBLIC inPublic;
  TPM2B_DIGEST outsideInfo;
  TPML_PCR_SELECTION creationPCR;
  TPM2B_PRIVATE outPrivate;
  TPM2B_PUBLIC outPublic;
  TPM2B_CREATION_DATA creationData;
  TPM2B_DIGEST creationHash;
  TPMT_TK_CREATION creationTicket;
  TSS2L_SYS_AUTH_RESPONSE rspAuthsArray;

  // Consume data for each parameter from the stream
  stream.ConsumeData(&cmdAuthsArray, sizeof(cmdAuthsArray));
  stream.ConsumeData(&inSensitive, sizeof(inSensitive));
  stream.ConsumeData(&inPublic, sizeof(inPublic));
  stream.ConsumeData(&outsideInfo, sizeof(outsideInfo));
  stream.ConsumeData(&creationPCR, sizeof(creationPCR));
  stream.ConsumeData(&outPrivate, sizeof(outPrivate));
  stream.ConsumeData(&outPublic, sizeof(outPublic));
  stream.ConsumeData(&creationData, sizeof(creationData));
  stream.ConsumeData(&creationHash, sizeof(creationHash));
  stream.ConsumeData(&creationTicket, sizeof(creationTicket));
  stream.ConsumeData(&rspAuthsArray, sizeof(rspAuthsArray));

  // Call the function to fuzz
  Tss2_Sys_Create(sysContext, parentHandle, &cmdAuthsArray, &inSensitive, &inPublic, &outsideInfo, &creationPCR, &outPrivate, &outPublic, &creationData, &creationHash, &creationTicket, &rspAuthsArray);

  // Cleanup
  Tss2_Sys_Finalize(sysContext);
  free(sysContext);

  return 0;
}