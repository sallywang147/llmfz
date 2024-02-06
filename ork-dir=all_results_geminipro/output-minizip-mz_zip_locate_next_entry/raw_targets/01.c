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
  const std::string zip_data = stream.ConsumeRemainingBytesAsString();
  const size_t zip_size = zip_data.size();
  void* zip_handle = mz_zip_open(zip_data.c_str(), zip_size, MZ_OPEN_MODE_READ);
  if (zip_handle == nullptr) {
    return 0;
  }

  void* userdata = nullptr;
  int result = mz_zip_locate_next_entry(zip_handle, userdata, nullptr);
  mz_zip_close(zip_handle);
  return result;
}