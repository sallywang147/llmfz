#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_mem.h"
#include "mz_zip.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/

#define MZ_FUZZ_TEST_FILENAME "foo"

/***************************************************************************/

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  mz_zip_archive archive;
  void *fuzz_stream = NULL;
  void *stream = NULL;
  void *handle = NULL;
  int32_t err = MZ_OK;
  uint16_t value16 = 0;
  uint8_t value8 = 0;
  int16_t compress_level = 0;
  int64_t fuzz_pos = 0;
  int32_t fuzz_length = 0;
  uint8_t *fuzz_buf = NULL;
  char *filename = NULL;
  char *password = NULL;
  size_t filename_size = 0;
  size_t password_size = 0;
  FILE *fp = NULL;

  fuzz_stream = mz_stream_mem_create();
  if (!fuzz_stream)
    return 1;
  mz_stream_mem_set_buffer(fuzz_stream, (void *)data, (int32_t)size);

  memset(&archive, 0, sizeof(archive));

  archive.flag = MZ_ZIP_FLAG_UTF8;
  if ((mz_stream_read_uint8(fuzz_stream, &value8) == MZ_OK) && (value8 < 0x08)) {
    if (mz_stream_read_uint16(fuzz_stream, &value16) == MZ_OK)
      archive.flag = value16;
  }
  archive.compression_method = MZ_COMPRESS_METHOD_DEFLATE;
  if ((mz_stream_read_uint8(fuzz_stream, &value8) == MZ_OK) && (value8 < 0x08)) {
    if (mz_stream_read_uint16(fuzz_stream, &value16) == MZ_OK)
      archive.compression_method = value16;
  }

  if ((mz_stream_read_uint8(fuzz_stream, &value8) == MZ_OK) && (value8 < 0x08)) {
    if (mz_stream_read_uint16(fuzz_stream, &value16) == MZ_OK)
      archive.zip64 = value16;
  }

  filename = MZ_FUZZ_TEST_FILENAME;
  filename_size = (uint16_t)strlen(MZ_FUZZ_TEST_FILENAME);

  compress_level = MZ_COMPRESS_LEVEL_DEFAULT;
  if ((mz_stream_read_uint8(fuzz_stream, &value8) == MZ_OK) && (value8 < 0x08)) {
    if (mz_stream_read_uint16(fuzz_stream, &value16) == MZ_OK)
      compress_level = value16;
  }

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
    mz_stream_mem_get_buffer_at_current(fuzz_stream, (const void **)&fuzz_buf);
    fuzz_pos = mz_stream_tell(fuzz_stream);
    mz_stream_mem_get_buffer_length(fuzz_stream, &fuzz_length);

    fp = fopen(filename, "wb");
    if (fp) {
      fwrite(fuzz_buf, 1, (fuzz_length - (int32_t)fuzz_pos), fp);
      fclose(fp);

      err = mz_zip_writer_add_cfile(
          &archive, filename, fopen(filename, "rb"), 0, NULL, NULL, compress_level, 0, password, password_size, NULL, 0);

      mz_zip_entry_close(handle);
    }

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