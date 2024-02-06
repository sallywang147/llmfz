#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  FT_Library library;
  if (FT_Init_FreeType(&library)) {
    return 0;
  }

  FT_Face face;
  if (FT_New_Memory_Face(library, data, size, 0, &face)) {
    FT_Done_FreeType(library);
    return 0;
  }

  FT_Set_Pixel_Sizes(face, 0, 16);

  FT_GlyphSlot slot = face->glyph;

  int glyph_index = fdp.ConsumeIntegralInRange<int>(0, face->num_glyphs - 1);
  int load_flags = fdp.ConsumeIntegral<int>();

  if (tt_glyph_load(slot, nullptr, glyph_index, load_flags)) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}