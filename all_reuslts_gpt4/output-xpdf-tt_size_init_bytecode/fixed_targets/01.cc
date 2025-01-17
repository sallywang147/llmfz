#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_INTERNAL_OBJECTS_H
#include FT_INTERNAL_DEBUG_H

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

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

  FT_Size size_obj;
  error = FT_New_Size(face, &size_obj);
  if (error) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  error = FT_Activate_Size(size_obj);
  if (error) {
    FT_Done_Size(size_obj);
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  char pedantic = stream.ConsumeIntegral<char>();
  int result = tt_size_init_bytecode((struct FT_SizeRec_ *)size_obj, pedantic);

  FT_Done_Size(size_obj);
  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}