#include <fuzzer/FuzzedDataProvider.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_TRUETYPE_TABLES_H

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize freetype library
  FT_Library library;
  if (FT_Init_FreeType(&library))
    return 0;

  // Create a new face object
  FT_Face face;
  if (FT_New_Memory_Face(library, data, size, 0, &face)) {
    FT_Done_FreeType(library);
    return 0;
  }

  // Set the character size and use the size object
  if (FT_Set_Char_Size(face, 0, 16*64, 300, 300)) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  // Extract the pedantic parameter
  char pedantic = stream.ConsumeIntegral<char>();

  // Call the target function
  int result = tt_size_ready_bytecode(face->size, pedantic);

  // Clean up
  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return result;
}