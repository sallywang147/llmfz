#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "TpmBuildSwitches.h"
#include "TpmTcpProtocol.h"
#include "Implementation.h"
#include "Manufacture_fp.h"
#include "Platform_fp.h"
#include "Simulator_fp.h"
#include "CreatePrimary_fp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize TPM
  _plat__NVEnable(NULL);
  if (TPM_Manufacture(1) != 0) {
    dprintf(STDERR_FILENO, "[FAILED] manufacturing\n");
    exit(1);
  }
  _rpc__Signal_PowerOn(FALSE);
  _rpc__Signal_NvOn();

  // Initialize the CreatePrimary_In struct
  CreatePrimary_In in;
  memset(&in, 0, sizeof(in));

  // Consume data for the CreatePrimary_In struct
  in.primaryHandle = stream.ConsumeIntegral<TPMI_RH_HIERARCHY>();
  in.inSensitive.t.sensitive.userAuth.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(in.inSensitive.t.sensitive.userAuth.t.buffer));
  memcpy(in.inSensitive.t.sensitive.userAuth.t.buffer, stream.ConsumeBytes<uint8_t>(in.inSensitive.t.sensitive.userAuth.t.size).data(), in.inSensitive.t.sensitive.userAuth.t.size);
  in.inSensitive.t.sensitive.data.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(in.inSensitive.t.sensitive.data.t.buffer));
  memcpy(in.inSensitive.t.sensitive.data.t.buffer, stream.ConsumeBytes<uint8_t>(in.inSensitive.t.sensitive.data.t.size).data(), in.inSensitive.t.sensitive.data.t.size);
  in.inPublic.t.publicArea.objectAttributes.val = stream.ConsumeIntegral<uint32_t>();
  in.inPublic.t.publicArea.authPolicy.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(in.inPublic.t.publicArea.authPolicy.t.buffer));
  memcpy(in.inPublic.t.publicArea.authPolicy.t.buffer, stream.ConsumeBytes<uint8_t>(in.inPublic.t.publicArea.authPolicy.t.size).data(), in.inPublic.t.publicArea.authPolicy.t.size);
  in.inPublic.t.publicArea.type = stream.ConsumeIntegral<TPMI_ALG_PUBLIC>();
  in.inPublic.t.publicArea.nameAlg = stream.ConsumeIntegral<TPMI_ALG_HASH>();
  in.inPublic.t.publicArea.parameters.rsaDetail.symmetric.algorithm = stream.ConsumeIntegral<TPMI_ALG_SYM_OBJECT>();
  in.inPublic.t.publicArea.parameters.rsaDetail.symmetric.keyBits.aes = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.t.publicArea.parameters.rsaDetail.symmetric.mode.aes = stream.ConsumeIntegral<TPMI_ALG_SYM_MODE>();
  in.inPublic.t.publicArea.parameters.rsaDetail.scheme.scheme = stream.ConsumeIntegral<TPMI_ALG_RSA_SCHEME>();
  in.inPublic.t.publicArea.parameters.rsaDetail.keyBits = stream.ConsumeIntegral<uint16_t>();
  in.inPublic.t.publicArea.parameters.rsaDetail.exponent = stream.ConsumeIntegral<uint32_t>();
  in.inPublic.t.publicArea.unique.rsa.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(in.inPublic.t.publicArea.unique.rsa.t.buffer));
  memcpy(in.inPublic.t.publicArea.unique.rsa.t.buffer, stream.ConsumeBytes<uint8_t>(in.inPublic.t.publicArea.unique.rsa.t.size).data(), in.inPublic.t.publicArea.unique.rsa.t.size);
  in.outsideInfo.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(in.outsideInfo.t.buffer));
  memcpy(in.outsideInfo.t.buffer, stream.ConsumeBytes<uint8_t>(in.outsideInfo.t.size).data(), in.outsideInfo.t.size);
  in.creationPCR.count = stream.ConsumeIntegralInRange<uint32_t>(0, sizeof(in.creationPCR.pcrSelections));
  for (uint32_t i = 0; i < in.creationPCR.count; i++) {
    in.creationPCR.pcrSelections[i].hash = stream.ConsumeIntegral<TPMI_ALG_HASH>();
    in.creationPCR.pcrSelections[i].sizeofSelect = stream.ConsumeIntegralInRange<uint8_t>(0, sizeof(in.creationPCR.pcrSelections[i].pcrSelect));
    memcpy(in.creationPCR.pcrSelections[i].pcrSelect, stream.ConsumeBytes<uint8_t>(in.creationPCR.pcrSelections[i].sizeofSelect).data(), in.creationPCR.pcrSelections[i].sizeofSelect);
  }

  // Initialize the CreatePrimary_Out struct
  CreatePrimary_Out out;
  memset(&out, 0, sizeof(out));

  // Call the function to fuzz
  TPM2_CreatePrimary(&in, &out);

  return 0;
}