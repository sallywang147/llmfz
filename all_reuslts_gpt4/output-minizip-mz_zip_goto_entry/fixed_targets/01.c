#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mz_zip.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a zip handle
  mz_zip_handle *zip_handle = mz_zip_create(NULL);
  if (zip_handle == NULL) {
    return 0;
  }

  // Consume data to create a zip archive
  std::vector<uint8_t> zip_data = stream.ConsumeRemainingBytes<uint8_t>();
  mz_zip_open_buffer(zip_handle, zip_data.data(), zip_data.size(), 0);

  // Consume data to get a cd_pos
  size_t cd_pos = stream.ConsumeIntegral<size_t>();

  // Call the function to fuzz
  mz_zip_goto_entry(zip_handle, cd_pos);

  // Clean up
  mz_zip_delete(&zip_handle);

  return 0;
}