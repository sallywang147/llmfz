#include <tpm2.h>

extern "C" {
#include <tss2/tss2_sys.h>
}

int main() {
  TSS2_SYS_CONTEXT *sys_ctx;
  TSS2_TCTI_CONTEXT *tcti_ctx;
  TPM2B_SENSITIVE_CREATE inSensitive = {0};
  TPM2B_PUBLIC inPublic = {0};
  TPM2B_DATA outsideInfo = {0};
  TPML_PCR_SELECTION creationPCR = {0};
  TPM2B_PUBLIC *outPublic;
  TPM2B_CREATION_DATA *creationData;
  TPM2B_DIGEST *creationHash;
  TPM2B_NAME *name;
  TPM2_HANDLE handle;
  UINT32 rval;

  tcti_ctx = tss2_tcti_default_init();
  sys_ctx = tss2_sys_init(tcti_ctx);

  rval = TPM2_CreatePrimary(sys_ctx, TPM2_RH_OWNER, &inSensitive, &inPublic, &outsideInfo, &creationPCR, &handle, &outPublic, &creationData, &creationHash, &name);

  tss2_sys_finalize(sys_ctx);
  tss2_tcti_finalize(tcti_ctx);

  return 0;
}