#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mz_zip.h"

// Define a callback function for mz_zip_locate_next_entry
int cb_func(char *handle, char *userdata) {
  // For simplicity, we just return 0
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for handle and userdata
  std::string handle_str = stream.ConsumeRandomLengthString();
  std::string userdata_str = stream.ConsumeRemainingBytesAsString();

  // Convert strings to char pointers
  char *handle = const_cast<char*>(handle_str.c_str());
  char *userdata = const_cast<char*>(userdata_str.c_str());

  // Call the target function
  mz_zip_locate_next_entry(handle, userdata, cb_func);

  return 0;
}