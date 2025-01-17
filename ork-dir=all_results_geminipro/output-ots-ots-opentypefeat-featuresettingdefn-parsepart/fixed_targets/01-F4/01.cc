#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"
#include "ots.h"

namespace ots {

bool OpenTypeFEAT::FeatureSettingDefn::ParsePart(OpenTypeFEAT::FeatureSettingDefn *this, Buffer *table) {
  uint16_t setting_count;
  if (!table->ReadU16(&setting_count)) {
    return OTS_FAILURE();
  }
  this->setting_count = setting_count;
  this->settings = new uint16_t[setting_count];
  for (unsigned i = 0; i < setting_count; ++i) {
    if (!table->ReadU16(&this->settings[i])) {
      return OTS_FAILURE();
    }
  }
  return true;
}

}  // namespace ots

extern "C" {

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::Buffer table(data, size);
  ots::OpenTypeFEAT::FeatureSettingDefn setting_defn;
  ots::OpenTypeFEAT::FeatureSettingDefn::ParsePart(&setting_defn, &table);
  return 0;
}

}  // extern "C"