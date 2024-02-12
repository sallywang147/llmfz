 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "gzip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  FT_Library library;
  FT_Init_FreeType(&library);

  FT_Stream stream_ft;
  stream_ft.memory = const_cast<uint8_t*>(data);
  stream_ft.size = size;
  stream_ft.pos = 0;
  stream_ft.cursor = stream_ft.memory;
  stream_ft.read = [](FT_Stream stream, unsigned long offset,
                       unsigned char* buffer, unsigned long count) {
    if (offset + count > stream->size) {
      return -1;
    }
    memcpy(buffer, stream->memory + offset, count);
    return 0;
  };
  stream_ft.close = [](FT_Stream) { return 0; };

  FT_Face face;
  FT_New_Face(library, &stream_ft, 0, &face);

  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}