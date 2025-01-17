#include <fuzzer/FuzzedDataProvider.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TRUETYPE_H

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  FT_Library library;
  FT_Face face;
  FT_Error error;

  error = FT_Init_FreeType(&library);
  if (error) {
    return 0;
  }

  error = FT_New_Memory_Face(library, data, size, 0, &face);
  if (error) {
    FT_Done_FreeType(library);
    return 0;
  }

  error = FT_Set_Pixel_Sizes(face, 0, 16);
  if (error) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  TT_Size tt_size = (TT_Size)face->size;
  FT_GlyphSlot glyph = face->glyph;
  int glyph_index = fdp.ConsumeIntegralInRange<int>(0, face->num_glyphs - 1);
  int load_flags = fdp.ConsumeIntegral<int>();

  TT_Load_Glyph(tt_size, glyph, glyph_index, load_flags);

  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}