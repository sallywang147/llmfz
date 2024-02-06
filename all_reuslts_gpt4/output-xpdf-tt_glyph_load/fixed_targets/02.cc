#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_INTERNAL_OBJECTS_H
#include FT_INTERNAL_DEBUG_H
#include FT_OUTLINE_H

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
  FT_Size size_obj;
  if (FT_Request_Size(face, &size_obj)) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  // Prepare parameters for tt_glyph_load
  FT_GlyphSlot slot = face->glyph;
  int glyph_index = stream.ConsumeIntegralInRange<int>(0, face->num_glyphs - 1);
  int load_flags = stream.ConsumeIntegral<int>();

  // Call the target function
  tt_glyph_load(slot, size_obj, glyph_index, load_flags);

  // Cleanup
  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}