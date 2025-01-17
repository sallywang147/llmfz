#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"
#include "ots.h"

namespace {

class FEAT {
 public:
  bool ParsePart(ots::Buffer *table) {
    return ots::OpenTypeFEAT::FeatureSettingDefn::ParsePart(this, table);
  }
};

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::ExpandingMemoryStream stream(size /*initial*/, size * 8 /*limit*/);
  stream.WriteRaw(data, size);
  stream.Seek(0);

  FEAT feat;
  feat.ParsePart(&stream);

  return 0;
}