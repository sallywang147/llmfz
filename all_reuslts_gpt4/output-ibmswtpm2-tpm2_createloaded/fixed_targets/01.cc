#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "TpmBuildSwitches.h"
#include "CreateLoaded_fp.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  CreateLoaded_In in;
  CreateLoaded_Out out;

  // Initialize the 'in' structure
  in.parentHandle = stream.ConsumeIntegral<TPMI_DH_OBJECT>();
  in.inSensitive.sensitive.userAuth.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, TPMU_HA_MAX);
  memcpy(in.inSensitive.sensitive.userAuth.t.buffer, stream.ConsumeBytes<uint8_t>(in.inSensitive.sensitive.userAuth.t.size).data(), in.inSensitive.sensitive.userAuth.t.size);
  in.inSensitive.sensitive.data.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(TPMU_SENSITIVE_COMPOSITE));
  memcpy(in.inSensitive.sensitive.data.t.buffer, stream.ConsumeBytes<uint8_t>(in.inSensitive.sensitive.data.t.size).data(), in.inSensitive.sensitive.data.t.size);
  in.inPublic.publicArea.type = stream.ConsumeIntegral<TPMI_ALG_PUBLIC>();
  in.inPublic.publicArea.nameAlg = stream.ConsumeIntegral<TPMI_ALG_HASH>();
  in.inPublic.publicArea.objectAttributes.val = stream.ConsumeIntegral<TPMA_OBJECT>();
  in.inPublic.publicArea.authPolicy.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(TPMT_HA));
  memcpy(in.inPublic.publicArea.authPolicy.t.buffer, stream.ConsumeBytes<uint8_t>(in.inPublic.publicArea.authPolicy.t.size).data(), in.inPublic.publicArea.authPolicy.t.size);
  in.inPublic.publicArea.parameters.keyedHashDetail.scheme.scheme = stream.ConsumeIntegral<TPMI_ALG_KEYEDHASH_SCHEME>();
  in.inPublic.publicArea.parameters.keyedHashDetail.scheme.details.anySig.hashAlg = stream.ConsumeIntegral<TPMI_ALG_HASH>();
  in.inPublic.publicArea.unique.keyedHash.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(TPMU_PUBLIC_ID));
  memcpy(in.inPublic.publicArea.unique.keyedHash.t.buffer, stream.ConsumeBytes<uint8_t>(in.inPublic.publicArea.unique.keyedHash.t.size).data(), in.inPublic.publicArea.unique.keyedHash.t.size);
  in.outsideInfo.t.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(TPMS_PCR_SELECT));
  memcpy(in.outsideInfo.t.buffer, stream.ConsumeBytes<uint8_t>(in.outsideInfo.t.size).data(), in.outsideInfo.t.size);
  in.creationPCR.count = stream.ConsumeIntegralInRange<uint32_t>(0, HASH_COUNT);
  for(uint32_t i = 0; i < in.creationPCR.count; i++)
    in.creationPCR.pcrSelections[i].hash = stream.ConsumeIntegral<TPMI_ALG_HASH>();

  // Call the function to fuzz
  TPM2_CreateLoaded(&in, &out);

  return 0;
}