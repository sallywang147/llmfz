#include "ivorbisfile.h"
#include <cstdint>
#include <stdio.h>
#include <string.h>

#define INPUT_LIMIT 16384

struct vorbis_data {
  const uint8_t *current;
  const uint8_t *data;
  size_t size;
};

size_t read_func(void *ptr, size_t size1, size_t size2, void *datasource) {
  vorbis_data *vd = (vorbis_data *)(datasource);
  size_t len = size1 * size2;
  if (vd->current + len > vd->data + vd->size) {
    len = vd->data + vd->size - vd->current;
  }
  memcpy(ptr, vd->current, len);
  vd->current += len;
  return len;
}

int close_func(void *) { return 0; }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ov_callbacks memory_callbacks = {0};
  memory_callbacks.read_func = read_func;
  memory_callbacks.close_func = close_func;
  vorbis_data data_st;
  data_st.size = Size > INPUT_LIMIT ? INPUT_LIMIT : Size;
  data_st.current = Data;
  data_st.data = Data;
  OggVorbis_File vf;
  int result = ov_open_callbacks(&vf, &data_st, NULL, 0, memory_callbacks);
  if (result == 0) {
    ov_clear(&vf);
  }
  return 0;
}