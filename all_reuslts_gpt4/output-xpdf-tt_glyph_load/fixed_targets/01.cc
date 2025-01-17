#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_INTERNAL_OBJECTS_H
#include FT_INTERNAL_DEBUG_H
#include FT_OUTLINE_H

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  FT_Library library;
  FT_Face face;
  FT_Error error;
  FT_GlyphSlot slot;
  FT_Size size_ft;

  // Initialize FreeType library
  error = FT_Init_FreeType(&library);
  if (error) {
    return 0;
  }

  // Create a new face object
  error = FT_New_Face(library, "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 0, &face);
  if (error) {
    FT_Done_FreeType(library);
    return 0;
  }

  // Extract glyph index and load flags
  int glyph_index = stream.ConsumeIntegral<int>();
  int load_flags = stream.ConsumeIntegral<int>();

  // Extract size parameters
  FT_F26Dot6 char_width = stream.ConsumeIntegral<FT_F26Dot6>();
  FT_F26Dot6 char_height = stream.ConsumeIntegral<FT_F26Dot6>();
  FT_UInt horz_resolution = stream.ConsumeIntegral<FT_UInt>();
  FT_UInt vert_resolution = stream.ConsumeIntegral<FT_UInt>();

  // Set char size
  error = FT_Set_Char_Size(face, char_width, char_height, horz_resolution, vert_resolution);
  if (error) {
    FT_Done_Face(face);
    FT_Done_FreeType(library);
    return 0;
  }

  // Get slot and size
  slot = face->glyph;
  size_ft = face->size;

  // Call the function to fuzz
  tt_glyph_load(slot, size_ft, glyph_index, load_flags);

  // Clean up
  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}