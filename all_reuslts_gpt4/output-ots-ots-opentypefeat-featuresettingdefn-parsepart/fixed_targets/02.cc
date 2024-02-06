#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  ots::OpenTypeFEAT::FeatureSettingDefn featureSettingDefn;
  ots::Buffer table(stream.ConsumeRemainingBytes<uint8_t>().data(), size);

  featureSettingDefn.ParsePart(&featureSettingDefn, &table);

  return 0;
}