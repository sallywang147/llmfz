 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Tpm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  CreateLoaded_In in;
  in.inPublic.publicArea.type = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.nameAlg = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.objectAttributes =
      stream.ConsumeIntegral<uint32_t>();
  in.inPublic.publicArea.authPolicy.size = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.publicArea.authPolicy.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  in.inPrivate.size = stream.ConsumeIntegral<uint32_t>();
  in.inPrivate.buffer = reinterpret_cast<uint8_t*>(const_cast<char*>(
      stream.ConsumeRemainingBytesAsString().c_str()));
  in.inSensitive.sensitive.authValue.size =
      stream.ConsumeIntegral<uint16_t>();
  in.inSensitive.sensitive.authValue.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  in.inSensitive.sensitive.seedValue.size =
      stream.ConsumeIntegral<uint16_t>();
  in.inSensitive.sensitive.seedValue.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  in.inSensitive.sensitive.sensitive.size =
      stream.ConsumeIntegral<uint16_t>();
  in.inSensitive.sensitive.sensitive.buffer =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  in.parentHandle = stream.ConsumeIntegral<uint32_t>();
  in.creationPCR.size = stream.ConsumeIntegral<uint32_t>();
  in.creationPCR.pcrSelection.sizeOfSelect =
      stream.ConsumeIntegral<uint8_t>();
  in.creationPCR.pcrSelection.pcrSelect =
      reinterpret_cast<uint8_t*>(const_cast<char*>(
          stream.ConsumeRemainingBytesAsString().c_str()));
  in.outsideInfo.size = stream.ConsumeIntegral<uint32_t>();
  in.outsideInfo.buffer = reinterpret_cast<uint8_t*>(const_cast<char*>(
      stream.ConsumeRemainingBytesAsString().c_str()));

  CreateLoaded_Out out;
  int ret = TPM2_CreateLoaded(&in, &out);
  if (ret != TPM_RC_SUCCESS) {
    return 0;
  }

  return 0;
}