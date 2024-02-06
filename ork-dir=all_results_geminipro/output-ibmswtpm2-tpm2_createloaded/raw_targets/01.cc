#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" {
#include "tpm2.h"
#include "tpm2_alg_util.h"
#include "tpm2_capability.h"
#include "tpm2_common.h"
#include "tpm2_create.h"
#include "tpm2_nv_util.h"
#include "tpm2_options.h"
#include "tpm2_session.h"
#include "tpm2_tool.h"
#include "tpm2_util.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(uint32_t)) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  TPM2B_PUBLIC inPublic = {0};
  inPublic.size = sizeof(inPublic);
  inPublic.publicArea.type = TPM2_ALG_RSA;
  inPublic.publicArea.parameters.rsaDetail.symmetric.algorithm =
      TPM2_ALG_AES;
  inPublic.publicArea.parameters.rsaDetail.symmetric.keyBits.aes = 128;
  inPublic.publicArea.parameters.rsaDetail.symmetric.mode.aes =
      TPM2_ALG_CFB;
  inPublic.publicArea.parameters.rsaDetail.scheme.scheme = TPM2_ALG_NULL;
  inPublic.publicArea.parameters.rsaDetail.keyBits = 2048;
  inPublic.publicArea.parameters.rsaDetail.exponent = 0;
  inPublic.publicArea.nameAlg = TPM2_ALG_SHA256;

  TPM2B_SENSITIVE_CREATE inSensitive = {0};
  inSensitive.size = sizeof(inSensitive);
  inSensitive.sensitive.data.size = 0;

  TPM2B_DATA outsideInfo = {0};
  TPM2B_PUBLIC template = {0};

  TPM2B_NAME name = {0};
  TPM2B_DIGEST qualData = {0};

  TPM2B_PRIVATE *outPrivate = NULL;
  TPM2B_PUBLIC *outPublic = NULL;

  TPMI_DH_OBJECT parentHandle = TPM2_RH_NULL;
  TPM2B_DATA label = {0};
  TPM2B_PRIVATE *inPrivate = NULL;

  TPML_PCR_SELECTION creationPCR = {0};
  TPM2_HANDLE shandle1 = TPM2_RS_PW;
  TPM2_HANDLE shandle2 = TPM2_RS_PW;
  TPM2_HANDLE shandle3 = TPM2_RS_PW;

  uint32_t sessionAttributes = 0;
  TPM2_SE session1 = {0};
  TPM2_SE session2 = {0};
  TPM2_SE session3 = {0};

  size_t offset = 0;
  uint32_t tmp32;
  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.type = TPM2_ALG_ECC;
    inPublic.publicArea.parameters.eccDetail.symmetric.algorithm =
        TPM2_ALG_AES;
    inPublic.publicArea.parameters.eccDetail.symmetric.keyBits.aes = 128;
    inPublic.publicArea.parameters.eccDetail.symmetric.mode.aes =
        TPM2_ALG_CFB;
    inPublic.publicArea.parameters.eccDetail.scheme.scheme = TPM2_ALG_NULL;
    inPublic.publicArea.parameters.eccDetail.curveID = TPM2_ECC_NIST_P256;
    inPublic.publicArea.parameters.eccDetail.kdf.scheme = TPM2_ALG_NULL;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.nameAlg = TPM2_ALG_SHA1;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_RESTRICTED;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_DECRYPT;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_SIGN_ENCRYPT;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_FIXEDTPM;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_FIXEDPARENT;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_SENSITIVEDATAORIGIN;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_USERWITHAUTH;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_SIGN;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_ADMINWITHPOLICY;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_NO_AUTHORIZATION_VAL;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_ENCRYPTED_DUPLICATION;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_RESTRICTED_DUPLICATION;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_ALLOW_HIERARCHY_CHANGE;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_DUPLICATION;
  }

  tmp32 = provider.ConsumeIntegralInRange<uint32_t>(0, 1);
  offset += sizeof(uint32_t);
  if (tmp32) {
    inPublic.publicArea.objectAttributes |= TPMA_OBJECT_PUBKEY_ONLY;
  }

  tmp32 = provider.Consume