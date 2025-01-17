#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H

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

  FT_Size size;
  if (FT_New_Size(face, &size)) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  FT_GlyphSlot slot;
  if (FT_Get_Glyph(face, 0, FT_LOAD_NO_BITMAP, &slot)) {
    FT_Done_Size(size);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  FT_Load_Glyph(size, slot, fdp.ConsumeIntegralInRange<int>(0, 1000),
                fdp.ConsumeIntegralInRange<int>(0, 1000));

  FT_Done_Size(size);
  FT_Done_Face(face);
  FT_Done_FreeType(library);
  return 0;
}