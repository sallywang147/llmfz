#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
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

  FT_GlyphSlot slot = face->glyph;
  FT_Size size;
  if (FT_New_Size(face, &size)) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  while (fdp.remaining_bytes() > 0) {
    int glyph_index = fdp.ConsumeIntegral<int32_t>();
    int load_flags = fdp.ConsumeIntegral<int32_t>();
    FT_Load_Glyph(face, glyph_index, load_flags);
    FT_Render_Glyph(slot, FT_RENDER_MODE_NORMAL);
  }

  FT_Done_Size(size);
  FT_Done_Face(face);
  FT_Done_FreeType(library);
  return 0;
}