#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"
#include "ots.h"

namespace ots {

bool OpenTypeGLAT_v2::GlatEntry::ParsePart(OpenTypeGLAT_v2::GlatEntry *this,
                                            Buffer *table) {
  uint32_t length;
  if (!table->ReadU32(&length)) {
    return Drop("Failed to read length");
  }
  if (length > table->length()) {
    return Drop("Length longer than table");
  }
  Buffer sub_table(*table);
  sub_table.set_limit(length);
  if (!this->Parse(&sub_table)) {
    return Drop("Failed to parse subtable");
  }
  table->Skip(length);
  return true;
}

}  // namespace ots

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::Buffer table(data, size);
  ots::OpenTypeGLAT_v2::GlatEntry entry;
  entry.ParsePart(&entry, &table);
  return 0;
}