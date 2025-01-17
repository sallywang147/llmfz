#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Tpm.h"

extern "C" {
#include "TpmTypes.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  TPM2B_PUBLIC inPublic;
  inPublic.publicArea.type = stream.ConsumeIntegral<uint16_t>();
  inPublic.publicArea.nameAlg = stream.ConsumeIntegral<uint16_t>();
  inPublic.publicArea.objectAttributes =
      stream.ConsumeIntegral<uint32_t>();
  inPublic.publicArea.authPolicy.size = stream.ConsumeIntegral<uint16_t>();
  inPublic.publicArea.authPolicy.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  TPM2B_PRIVATE inPrivate;
  inPrivate.size = stream.ConsumeIntegral<uint32_t>();
  inPrivate.buffer = reinterpret_cast<uint8_t*>(const_cast<char*>(
      stream.ConsumeRemainingBytesAsString().c_str()));
  TPM2B_SENSITIVE inSensitive;
  inSensitive.sensitive.authValue.size =
      stream.ConsumeIntegral<uint16_t>();
  inSensitive.sensitive.authValue.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  inSensitive.sensitive.seedValue.size =
      stream.ConsumeIntegral<uint16_t>();
  inSensitive.sensitive.seedValue.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  inSensitive.sensitive.sensitive.size =
      stream.ConsumeIntegral<uint16_t>();
  inSensitive.sensitive.sensitive.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  TPM2B_DATA creationPCR;
  creationPCR.size = stream.ConsumeIntegral<uint32_t>();
  creationPCR.pcrSelection.sizeOfSelect =
      stream.ConsumeIntegral<uint8_t>();
  creationPCR.pcrSelection.pcrSelect =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  TPM2B_CREATION_DATA creationData;
  creationData.size = stream.ConsumeIntegral<uint32_t>();
  creationData.buffer = reinterpret_cast<uint8_t*>(const_cast<char*>(
      stream.ConsumeRemainingBytesAsString().c_str()));

  TPM2B_PUBLIC outPublic;
  TPM2B_PRIVATE outPrivate;
  TPM2B_CREATION_DATA outCreationData;
  TPM2B_DIGEST outHash;
  TPMT_TK_CREATION outCreationTicket;

  int ret = TPM2_Create(0, &inPublic, &inPrivate, &inSensitive, &creationPCR,
                        &creationData, &outPublic, &outPrivate,
                        &outCreationData, &outHash, &outCreationTicket);
  if (ret != TPM_RC_SUCCESS) {
    return 0;
  }

  return 0;
}