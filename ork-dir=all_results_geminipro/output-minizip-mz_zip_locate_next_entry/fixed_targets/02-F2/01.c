#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_mem.h"
#include "mz_zip.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string zip_data = stream.ConsumeRemainingBytesAsString();
  void *fuzz_stream = mz_stream_mem_create();
  if (!fuzz_stream) {
    return 0;
  }
  mz_stream_mem_set_buffer(fuzz_stream,
                           reinterpret_cast<const void*>(zip_data.data()),
                           zip_data.size());

  char* handle = mz_zip_open(fuzz_stream, MZ_OPEN_MODE_READ);
  if (!handle) {
    mz_stream_mem_delete(&fuzz_stream);
    return 0;
  }

  struct mz_zip_file_s file_info;
  int err = MZ_OK;
  while (err == MZ_OK) {
    err = mz_zip_locate_next_entry(handle, NULL, NULL);
    if (err == MZ_OK) {
      mz_zip_entry_get_info(handle, &file_info);
    }
  }

  mz_zip_close(handle);
  mz_stream_mem_delete(&fuzz_stream);
  return 0;
}