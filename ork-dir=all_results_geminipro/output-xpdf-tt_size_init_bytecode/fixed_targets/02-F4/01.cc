#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_TRUETYPE_TABLES_H

extern "C" {
#include <freetype/tttables.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  FT_Library library;
  FT_Error error = FT_Init_FreeType(&library);
  if (error) {
    return 0;
  }

  FT_Face face;
  error = FT_New_Memory_Face(library, data, size, 0, &face);
  if (error) {
    FT_Done_FreeType(library);
    return 0;
  }

  FT_Size ftsize;
  error = FT_New_Size(face, &ftsize);
  if (error) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  char pedantic = fdp.ConsumeBool();

  FT_GlyphSlot slot = ftsize->glyph;
  FT_Glyph glyph;

  for (int i = 0; i < 1000; i++) {
    FT_UInt glyph_index = fdp.ConsumeIntegralInRange<FT_UInt>(0, face->num_glyphs);
    error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
    if (error) {
      continue;
    }
    error = FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
    if (error) {
      continue;
    }
    error = FT_Get_Glyph(slot, &glyph);
    if (error) {
      continue;
    }
    FT_Done_Glyph(glyph);
  }

  error = tt_size_init_bytecode(ftsize, pedantic);
  if (error) {
    FT_Done_Size(ftsize);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  FT_Done_Size(ftsize);
  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}