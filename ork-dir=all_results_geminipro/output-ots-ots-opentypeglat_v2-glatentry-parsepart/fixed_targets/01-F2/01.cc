#include <stddef.h>
#include <stdint.h>
#include <cstring>

#include "opentype-sanitiser.h"
#include "ots.h"

namespace ots {

bool OpenTypeGLAT_v2::GlatEntry::ParsePart(OpenTypeGLAT_v2::GlatEntry *this,
                                            Buffer *table) {
  Buffer subtable = table->ReadSubBuffer(this->offset, this->length);
  if (!subtable.ok()) {
    return OTS_FAILURE();
  }
  if (this->format == 1) {
    return ParseFormat1(&subtable);
  } else if (this->format == 2) {
    return ParseFormat2(&subtable);
  }
  return OTS_FAILURE();
}

bool OpenTypeGLAT_v2::GlatEntry::ParseFormat1(Buffer *table) {
  if (!table->ReadU16(&this->glyph_count)) {
    return OTS_FAILURE();
  }
  if (this->glyph_count == 0) {
    return OTS_FAILURE();
  }
  this->glyph_map = new uint16_t[this->glyph_count];
  if (!this->glyph_map) {
    return OTS_FAILURE();
  }
  for (unsigned int i = 0; i < this->glyph_count; ++i) {
    if (!table->ReadU16(&this->glyph_map[i])) {
      return OTS_FAILURE();
    }
  }
  return true;
}

bool OpenTypeGLAT_v2::GlatEntry::ParseFormat2(Buffer *table) {
  if (!table->ReadU16(&this->glyph_count)) {
    return OTS_FAILURE();
  }
  if (this->glyph_count == 0) {
    return OTS_FAILURE();
  }
  this->glyph_map = new uint16_t[this->glyph_count];
  if (!this->glyph_map) {
    return OTS_FAILURE();
  }
  for (unsigned int i = 0; i < this->glyph_count; ++i) {
    if (!table->ReadU16(&this->glyph_map[i])) {
      return OTS_FAILURE();
    }
  }
  if (!table->ReadU16(&this->coverage_index)) {
    return OTS_FAILURE();
  }
  return true;
}

}  // namespace ots

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::Buffer table;
  if (!table.Copy(data, size)) {
    return 0;
  }

  ots::OpenTypeGLAT_v2::GlatEntry entry;
  entry.ParsePart(&entry, &table);
  return 0;
}