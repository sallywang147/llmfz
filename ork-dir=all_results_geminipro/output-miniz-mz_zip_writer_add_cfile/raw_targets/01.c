#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_mem.h"
#include "mz_zip.h"
#include "mz_zip_writer.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************/

#define MZ_FUZZ_TEST_FILENAME "foo"

/***************************************************************************/

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct mz_zip_archive archive;
  void *stream = NULL;
  void *handle = NULL;
  int32_t err = MZ_OK;
  uint16_t value16 = 0;
  uint8_t value8 = 0;
  int16_t compress_level = 0;
  int64_t fuzz_pos = 0;
  int32_t fuzz_length = 0;
  uint8_t *fuzz_buf = NULL;
  size_t uncompressed_size = 0;
  size_t compressed_size = 0;

  stream = mz_stream_mem_create();
  if (!stream)
    return 1;
  mz_stream_mem_set_buffer(stream, (void *)data, (int32_t)size);

  memset(&archive, 0, sizeof(archive));

  archive.flag = MZ_ZIP_FLAG_UTF8;
  if ((mz_stream_read_uint8(stream, &value8) == MZ_OK) && (value8 < 0x08)) {
    if (mz_stream_read_uint16(stream, &value16) == MZ_OK)
      archive.flag = value16;
  }
  archive.compression_method = MZ_COMPRESS_METHOD_DEFLATE;
  if ((mz_stream_read_uint8(stream, &value8) == MZ_OK) && (value8 < 0x08)) {
    if (mz_stream_read_uint16(stream, &value16) == MZ_OK)
      archive.compression_method = value16;
  }

  compress_level = MZ_COMPRESS_LEVEL_DEFAULT;
  if ((mz_stream_read_uint8(stream, &value8) == MZ_OK) && (value8 < 0x08)) {
    if (mz_stream_read_uint16(stream, &value16) == MZ_OK)
      compress_level = value16;
  }

  handle = mz_zip_writer_create(&archive);
  if (!handle) {
    mz_stream_mem_delete(&stream);
    return 1;
  }

  err = mz_zip_writer_add_cfile(handle, MZ_FUZZ_TEST_FILENAME, stdin, 0, &uncompressed_size, NULL, compress_level, 0, NULL, 0, NULL, 0);
  if (err == MZ_OK) {
    mz_stream_mem_get_buffer_at_current(stream, (const void **)&fuzz_buf);
    fuzz_pos = mz_stream_tell(stream);
    mz_stream_mem_get_buffer_length(stream, &fuzz_length);

    err = mz_zip_writer_add_cfile(handle, MZ_FUZZ_TEST_FILENAME, stdin, uncompressed_size, &compressed_size, fuzz_buf, compress_level, 0, NULL, 0, NULL, 0);
  }

  mz_zip_writer_delete(&handle);
  mz_stream_mem_delete(&stream);

  return 0;
}

/***************************************************************************/

#ifdef __cplusplus
}
#endif