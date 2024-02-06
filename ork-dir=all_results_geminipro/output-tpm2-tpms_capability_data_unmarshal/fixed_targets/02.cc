#include <stdint.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>

struct TPMS_CAPABILITY_DATA {
  uint32_t TPMS_Capability;
  uint8_t TPMS_Sensors;
};

extern "C" int TPMS_CAPABILITY_DATA_Unmarshal(struct TPMS_CAPABILITY_DATA * target, char ** buffer, int * size) {
  FuzzedDataProvider dataProvider(*buffer, *size);
  target->TPMS_Capability = dataProvider.ConsumeIntegral<uint32_t>();
  target->TPMS_Sensors = dataProvider.ConsumeIntegral<uint8_t>();
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct TPMS_CAPABILITY_DATA target;
  TPMS_CAPABILITY_DATA_Unmarshal(&target, (char **)&data, (int *)&size);
  return 0;
}