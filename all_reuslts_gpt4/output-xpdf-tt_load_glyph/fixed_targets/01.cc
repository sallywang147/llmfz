#include <fuzzer/FuzzedDataProvider.h>
#include <ft2build.h>
#include FT_FREETYPE_H

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct TT_SizeRec_ size;
  struct FT_GlyphSlotRec_ glyph;
  int glyph_index = stream.ConsumeIntegral<int>();
  int load_flags = stream.ConsumeIntegral<int>();

  size.metrics.x_ppem = stream.ConsumeIntegral<FT_UShort>();
  size.metrics.y_ppem = stream.ConsumeIntegral<FT_UShort>();
  size.metrics.x_scale = stream.ConsumeIntegral<FT_Fixed>();
  size.metrics.y_scale = stream.ConsumeIntegral<FT_Fixed>();
  size.metrics.ascender = stream.ConsumeIntegral<FT_Pos>();
  size.metrics.descender = stream.ConsumeIntegral<FT_Pos>();
  size.metrics.height = stream.ConsumeIntegral<FT_Pos>();
  size.metrics.max_advance = stream.ConsumeIntegral<FT_Pos>();

  glyph.linearHoriAdvance = stream.ConsumeIntegral<FT_Fixed>();
  glyph.linearVertAdvance = stream.ConsumeIntegral<FT_Fixed>();
  glyph.advance.x = stream.ConsumeIntegral<FT_Pos>();
  glyph.advance.y = stream.ConsumeIntegral<FT_Pos>();
  glyph.format = stream.ConsumeEnum<FT_Glyph_Format>();
  glyph.bitmap_left = stream.ConsumeIntegral<int>();
  glyph.bitmap_top = stream.ConsumeIntegral<int>();

  TT_Load_Glyph(&size, &glyph, glyph_index, load_flags);

  return 0;
}