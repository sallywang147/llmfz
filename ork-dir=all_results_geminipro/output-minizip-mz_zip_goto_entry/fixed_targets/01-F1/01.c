#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_mem.h"
#include "mz_zip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string zip_bytes = stream.ConsumeRemainingBytesAsString();
  void* zip_stream = mz_stream_mem_create();
  if (zip_stream == nullptr) {
    return 0;
  }
  mz_stream_mem_set_buffer(zip_stream,
                           reinterpret_cast<const void*>(zip_bytes.data()),
                           zip_bytes.size());
  void* zip_handle = mz_zip_open(zip_stream, MZ_OPEN_MODE_READ);
  if (zip_handle == nullptr) {
    mz_stream_mem_delete(&zip_stream);
    return 0;
  }

  const size_t cd_pos = stream.ConsumeIntegral<size_t>();
  int result = mz_zip_goto_entry(zip_handle, cd_pos);

  mz_zip_close(zip_handle);
  mz_stream_mem_delete(&zip_stream);
  return result;
}