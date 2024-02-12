#include <stdio.h>
#include <tpm2.h>

extern "C" {
#include <tss2/tss2_tpm2_types.h>
#include <tss2/tss2_tpm2_structs.h>
}

int main() {
  TPM2B_PUBLIC inPublic = {
      .size = sizeof(TPM2B_PUBLIC),
      .publicArea = {
          .type = TPM2_ALG_RSA,
          .nameAlg = TPM2_ALG_SHA256,
          .objectAttributes = TPMA_OBJECT_RESTRICTED | TPMA_OBJECT_DECRYPT,
          .authPolicy = {
              .size = 0,
          },
          .parameters = {
              .rsaDetail = {
                  .symmetric = {
                      .algorithm = TPM2_ALG_AES,
                      .keyBits = {
                          .aes = 128,
                      },
                      .mode = {
                          .aes = TPM2_ALG_CFB,
                      },
                  },
                  .scheme = {
                      .scheme = TPM2_ALG_NULL,
                  },
                  .keyBits = 2048,
                  .exponent = 0,
              },
          },
          .unique = {
              .size = 0,
          },
      },
  };

  TPM2B_SENSITIVE_CREATE inSensitive = {
      .size = 0,
      .sensitive = {
          .userAuth = {
              .size = 0,
          },
          .data = {
              .size = 0,
          },
      },
  };

  TPML_PCR_SELECTION creationPCR = {
      .count = 0,
  };

  TPM2B_DATA outsideInfo = {
      .size = 0,
  };

  TPML_DIGEST creationHash = {
      .count = 0,
  };

  TPM2B_PUBLIC *outPublic;
  TPM2B_CREATION_DATA *creationData;
  TPM2B_DIGEST *creationHashOut;
  TPMT_TK_CREATION *creationTicket;

  TSS2_RC rc = TPM2_CreatePrimary(
      NULL,
      &inSensitive,
      &inPublic,
      &creationPCR,
      &outsideInfo,
      &creationHash,
      &outPublic,
      &creationData,
      &creationHashOut,
      &creationTicket);
  if (rc != TPM2_RC_SUCCESS) {
    printf("Error: TPM2_CreatePrimary failed with RC: 0x%x\n", rc);
    return 1;
  }

  printf("TPM2_CreatePrimary succeeded!\n");

  return 0;
}