#include "mz.h"
#include "mz_crypt.h"
#include "mz_zip.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/

#define MZ_FUZZ_TEST_FILENAME "foo"

/***************************************************************************/

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  void *fuzz_stream = NULL;
  void *stream = NULL;
  void *handle = NULL;
  int32_t err = MZ_OK;
  uint16_t value16 = 0;
  uint8_t value8 = 0;
  int key_length = 0;
  int iv_length = 0;
  int64_t fuzz_pos = 0;
  int32_t fuzz_length = 0;
  uint8_t *fuzz_buf = NULL;

  fuzz_stream = mz_stream_mem_create();
  if (!fuzz_stream)
    return 1;
  mz_stream_mem_set_buffer(fuzz_stream, (void *)data, (int32_t)size);

  stream = mz_stream_mem_create();
  if (!stream) {
    mz_stream_mem_delete(&fuzz_stream);
    return 1;
  }
  handle = mz_zip_create();
  if (!handle) {
    mz_stream_mem_delete(&stream);
    mz_stream_mem_delete(&fuzz_stream);
    return 1;
  }

  err = mz_zip_open(handle, stream, MZ_OPEN_MODE_CREATE | MZ_OPEN_MODE_WRITE);
  if (err == MZ_OK) {
    if ((mz_stream_read_uint8(fuzz_stream, &value8) == MZ_OK) && (value8 < 0x08)) {
      if (mz_stream_read_uint16(fuzz_stream, &value16) == MZ_OK)
        key_length = value16;
    }

    if ((mz_stream_read_uint8(fuzz_stream, &value8) == MZ_OK) && (value8 < 0x08)) {
      if (mz_stream_read_uint16(fuzz_stream, &value16) == MZ_OK)
        iv_length = value16;
    }

    mz_stream_mem_get_buffer_at_current(fuzz_stream, (const void **)&fuzz_buf);
    fuzz_pos = mz_stream_tell(fuzz_stream);
    mz_stream_mem_get_buffer_length(fuzz_stream, &fuzz_length);

    err = mz_crypt_aes_set_decrypt_key(handle, (char *)fuzz_buf, key_length, (char *)fuzz_buf, iv_length);

    mz_zip_close(handle);
  }

  mz_zip_delete(&handle);
  mz_stream_mem_delete(&stream);

  mz_stream_mem_delete(&fuzz_stream);

  return 0;
}

/***************************************************************************/

#ifdef __cplusplus
}
#endif