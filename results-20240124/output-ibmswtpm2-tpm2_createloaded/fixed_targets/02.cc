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
  inSensitive.sensitiveArea.authValue.size =
      stream.ConsumeIntegral<uint16_t>();
  inSensitive.sensitiveArea.authValue.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  inSensitive.sensitiveArea.seedValue.size =
      stream.ConsumeIntegral<uint16_t>();
  inSensitive.sensitiveArea.seedValue.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  inSensitive.sensitiveArea.sensitive.size =
      stream.ConsumeIntegral<uint16_t>();
  inSensitive.sensitiveArea.sensitive.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  TPM2B_DATA creationPCR;
  creationPCR.size = stream.ConsumeIntegral<uint32_t>();
  creationPCR.pcrSelect.sizeOfSelect =
      stream.ConsumeIntegral<uint8_t>();
  creationPCR.pcrSelect.pcrSelect =
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

  CreateLoaded_In in;
  in.inPublic = &inPublic;
  in.inPrivate = &inPrivate;
  in.inSensitive = &inSensitive;
  in.creationPCR = &creationPCR;
  in.creationData = &creationData;

  CreateLoaded_Out out;
  out.outPublic = &outPublic;
  out.outPrivate = &outPrivate;
  out.outCreationData = &outCreationData;
  out.outHash = &outHash;
  out.outCreationTicket = &outCreationTicket;

  int ret = TPM2_CreateLoaded(&in, &out);
  if (ret != TPM_RC_SUCCESS) {
    return 0;
  }

  return 0;
}