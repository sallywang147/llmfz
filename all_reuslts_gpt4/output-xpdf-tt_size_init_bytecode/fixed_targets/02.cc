#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_INTERNAL_OBJECTS_H

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
  error = FT_New_Memory_Face(library, data, size, 0, &face);
  if (error) {
    FT_Done_FreeType(library);
    return 0;
  }

  FT_SizeRec sizeRec;
  memset(&sizeRec, 0, sizeof(FT_SizeRec));
  sizeRec.face = face;

  char pedantic = stream.ConsumeIntegral<char>();

  tt_size_init_bytecode(&sizeRec, pedantic);

  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}