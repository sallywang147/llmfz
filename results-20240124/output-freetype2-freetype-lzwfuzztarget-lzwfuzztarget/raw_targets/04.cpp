 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "freetype/ft2build.h"
#include "freetype/freetype.h"
#include "freetype/ftlcdfil.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a new FT_Library object.
  FT_Library library;
  FT_Error error = FT_Init_FreeType(&library);
  if (error) {
    return 0;
  }

  // Create a new FT_Face object.
  FT_Face face;
  error = FT_New_Memory_Face(library, data, size, 0, &face);
  if (error) {
    FT_Done_FreeType(library);
    return 0;
  }

  // Create a new FT_LzwFuzzTarget object.
  freetype::LzwFuzzTarget target(face);

  // Call the LzwFuzzTarget constructor.
  target.LzwFuzzTarget(&target);

  // Destroy the FT_Face object.
  FT_Done_Face(face);

  // Destroy the FT_Library object.
  FT_Done_FreeType(library);

  return 0;
}