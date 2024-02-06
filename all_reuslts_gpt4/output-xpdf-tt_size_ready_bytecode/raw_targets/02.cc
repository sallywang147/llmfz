#include <fuzzer/FuzzedDataProvider.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_INTERNAL_OBJECTS_H

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider fdp(data, size);

  FT_Library library;
  FT_Error error = FT_Init_FreeType(&library);
  if (error) {
    return 0;
  }

  FT_Face face;
  error = FT_New_Face(library, "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 0, &face);
  if (error) {
    FT_Done_FreeType(library);
    return 0;
  }

  FT_Size sizeRec;
  error = FT_New_Size(face, &sizeRec);
  if (error) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  error = FT_Activate_Size(sizeRec);
  if (error) {
    FT_Done_Size(sizeRec);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  char pedantic = fdp.ConsumeIntegral<char>();

  tt_size_ready_bytecode((TT_Size)sizeRec, pedantic);

  FT_Done_Size(sizeRec);
  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}