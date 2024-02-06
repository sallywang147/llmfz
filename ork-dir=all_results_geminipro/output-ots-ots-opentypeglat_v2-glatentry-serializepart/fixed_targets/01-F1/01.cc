#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"
#include "ots.h"

namespace ots {

bool OpenTypeGLAT_v2::GlatEntry::SerializePart(
    const OpenTypeGLAT_v2::GlatEntry *entry,
    OTSStream *out) {
  return out->WriteU16(entry->glyph_id) &&
         out->WriteU16(entry->offset) &&
         out->WriteU16(entry->length);
}

}  // namespace ots

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::Buffer file(data, size);
  uint32_t version;
  if (!file.ReadU32(&version)) {
    return 0;
  }

  ots::OpenTypeGLAT_v2::GlatEntry entry;
  entry.glyph_id = 0;
  entry.offset = 0;
  entry.length = 0;
  ots::ExpandingMemoryStream out;
  ots::OpenTypeGLAT_v2::GlatEntry::SerializePart(&entry, &out);

  return 0;
}