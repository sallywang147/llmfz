#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tss2/tss2_tpm2_types.h>
#include <tss2/tss2_tpm2_structs.h>
#include <tss2/tss2_mu.h>
#include <tss2/tss2_sys.h>

extern "C" {
#include <tss2/tss2_tcti_device.h>
}

int main() {
    TSS2_RC rc;
    TSS2_TCTI_CONTEXT *tcti_ctx = NULL;
    TSS2_SYS_CONTEXT *sys_ctx = NULL;
    TPM2B_PUBLIC inPublic = {0};
    TPM2B_SENSITIVE_CREATE inSensitive = {0};
    TPM2B_DATA outsideInfo = {0};
    TPML_PCR_SELECTION creationPCR = {0};
    TPM2B_PUBLIC outPublic = {0};
    TPM2B_CREATION_DATA creationData = {0};
    TPM2B_DIGEST creationHash = {0};
    TPMT_TK_CREATION creationTicket = {0};

    rc = Tss2_Tcti_Device_Init(&tcti_ctx, NULL);
    if (rc != TSS2_RC_SUCCESS) {
        fprintf(stderr, "Failed to initialize TCTI context: 0x%x\n", rc);
        return EXIT_FAILURE;
    }

    rc = Tss2_Sys_Initialize(tcti_ctx, &sys_ctx);
    if (rc != TSS2_RC_SUCCESS) {
        fprintf(stderr, "Failed to initialize SYS context: 0x%x\n", rc);
        return EXIT_FAILURE;
    }

    inPublic.publicArea.type = TPM2_ALG_RSA;
    inPublic.publicArea.nameAlg = TPM2_ALG_SHA256;
    inPublic.publicArea.objectAttributes = TPMA_OBJECT_RESTRICTED | TPMA_OBJECT_DECRYPT | TPMA_OBJECT_FIXEDTPM | TPMA_OBJECT_FIXEDPARENT | TPMA_OBJECT_SENSITIVEDATAORIGIN;
    inPublic.publicArea.authPolicy.size = 0;
    inPublic.publicArea.parameters.rsaDetail.symmetric.algorithm = TPM2_ALG_AES;
    inPublic.publicArea.parameters.rsaDetail.symmetric.keyBits.aes = 128;
    inPublic.publicArea.parameters.rsaDetail.symmetric.mode.aes = TPM2_ALG_CFB;
    inPublic.publicArea.parameters.rsaDetail.scheme.scheme = TPM2_ALG_RSAES;
    inPublic.publicArea.parameters.rsaDetail.scheme.details.oaep.hashAlg = TPM2_ALG_SHA256;

    inSensitive.sensitiveArea.algorithm = TPM2_ALG_RSA;
    inSensitive.sensitiveArea.nameAlg = TPM2_ALG_SHA256;
    inSensitive.sensitiveArea.sensitiveType = TPM2_ALG_RSA;
    inSensitive.sensitiveArea.authValue.size = 0;
    inSensitive.sensitiveArea.seedValue.size = 0;
    inSensitive.sensitiveArea.outsideInfo.size = 0;

    rc = Tss2_Sys_CreatePrimary(sys_ctx, TPM2_RH_OWNER, &inSensitive, &inPublic, &outsideInfo, &creationPCR, &outPublic, &creationData, &creationHash, &creationTicket);
    if (rc != TSS2_RC_SUCCESS) {
        fprintf(stderr, "Failed to create primary key: 0x%x\n", rc);
        return EXIT_FAILURE;
    }

    Tss2_Sys_Finalize(&sys_ctx);
    Tss2_Tcti_Finalize(&tcti_ctx);

    return EXIT_SUCCESS;
}