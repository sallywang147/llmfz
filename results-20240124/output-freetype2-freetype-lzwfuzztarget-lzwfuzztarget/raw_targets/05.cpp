 #include <ft2build.h>
#include FT_FREETYPE_H
#include FT_LZW_H
#include FT_OUTLINE_H
#include FT_IMAGE_H
#include FT_TRUETYPE_IDS_H
#include FT_TRUETYPE_TAGS_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static FT_Library library;
  static int library_init_result = FT_Init_FreeType(&library);
  if (library_init_result) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  const std::string font_path = stream.ConsumeRandomLengthString();
  FT_Face face;
  if (FT_New_Face(library, font_path.c_str(), 0, &face)) {
    return 0;
  }

  FT_GlyphSlot slot = face->glyph;

  // Select a random character.
  const int glyph_index = stream.ConsumeIntegralInRange<int>(0, face->num_glyphs);
  if (FT_Load_Glyph(face, glyph_index, FT_LOAD_NO_BITMAP)) {
    FT_Done_Face(face);
    return 0;
  }

  // Convert the outline to a bitmap.
  if (FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL)) {
    FT_Done_Face(face);
    return 0;
  }

  // Compress the bitmap using LZW.
  FT_LzwContext lzw_context;
  if (FT_Lzw_New_Context(&lzw_context, FT_LZW_MIN_CODE_BITS)) {
    FT_Done_Face(face);
    return 0;
  }

  FT_Lzw_Encode(lzw_context, slot->bitmap.buffer, slot->bitmap.width * slot->bitmap.rows);

  FT_Lzw_Done_Context(lzw_context);
  FT_Done_Face(face);

  return 0;
}