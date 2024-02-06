#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ots.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ots::OpenTypeFEAT::FeatureSettingDefn featureSettingDefn;
  ots::Buffer buffer(data, size);

  featureSettingDefn.ParsePart(&featureSettingDefn, &buffer);

  return 0;
}