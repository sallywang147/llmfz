#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tt_size.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  TT_SizeRec_ size;
  size.ptSize = fdp.ConsumeIntegral<float>();
  size.x_scale = fdp.ConsumeIntegral<float>();
  size.y_scale = fdp.ConsumeIntegral<float>();
  size.x_ppem = fdp.ConsumeIntegral<int32_t>();
  size.y_ppem = fdp.ConsumeIntegral<int32_t>();
  size.ascender = fdp.ConsumeIntegral<int32_t>();
  size.descender = fdp.ConsumeIntegral<int32_t>();
  size.line_gap = fdp.ConsumeIntegral<int32_t>();
  size.advance = fdp.ConsumeIntegral<int32_t>();
  size.bearing = fdp.ConsumeIntegral<int32_t>();
  size.width_max = fdp.ConsumeIntegral<int32_t>();
  size.height_max = fdp.ConsumeIntegral<int32_t>();
  size.subscript_x_size = fdp.ConsumeIntegral<int32_t>();
  size.subscript_y_size = fdp.ConsumeIntegral<int32_t>();
  size.subscript_x_offset = fdp.ConsumeIntegral<int32_t>();
  size.subscript_y_offset = fdp.ConsumeIntegral<int32_t>();
  size.superscript_x_size = fdp.ConsumeIntegral<int32_t>();
  size.superscript_y_size = fdp.ConsumeIntegral<int32_t>();
  size.superscript_x_offset = fdp.ConsumeIntegral<int32_t>();
  size.superscript_y_offset = fdp.ConsumeIntegral<int32_t>();
  size.strikeout_size = fdp.ConsumeIntegral<int32_t>();
  size.strikeout_offset = fdp.ConsumeIntegral<int32_t>();
  size.underline_size = fdp.ConsumeIntegral<int32_t>();
  size.underline_offset = fdp.ConsumeIntegral<int32_t>();
  size.overshoot = fdp.ConsumeIntegral<int32_t>();
  size.extra_space = fdp.ConsumeIntegral<int32_t>();
  size.num_glyphs = fdp.ConsumeIntegral<uint32_t>();
  size.glyph_widths = fdp.ConsumeRemainingBytes<int32_t>();

  tt_size_ready_bytecode(&size, 0);

  return 0;
}