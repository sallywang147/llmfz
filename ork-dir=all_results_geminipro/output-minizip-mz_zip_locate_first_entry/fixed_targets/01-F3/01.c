#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "mz.h"
#include "mz_strm.h"
#include "mz_strm_mem.h"
#include "mz_zip.h"
#include "mz_zip_entry.h"
#include "mz_zip_close.h"

extern "C" {
#include "mz_os.h"
#include "mz_strm_os.h"
#include "mz_zip_os.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string zip_file = stream.ConsumeRemainingBytesAsString();
  void* zip_handle = mz_zip_open(zip_file.c_str(), MZ_OPEN_MODE_READ);
  if (zip_handle == nullptr) {
    return 0;
  }

  // The user data is not used in this fuzzer.
  void* userdata = nullptr;

  // The callback function is not used in this fuzzer.
  int callback(void* userdata, mz_zip_archive* archive, mz_zip_file* file) {
    return 0;
  }

  int result = mz_zip_locate_first_entry(zip_handle, userdata, callback);
  mz_zip_close(zip_handle);
  return result;
}