#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "proton/data.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the pn_data_t object
  pn_data_t *pn_data = pn_data(0);
  if (pn_data == nullptr) {
    return 0;
  }

  // Consume data from the stream to fill the format string
  std::string format = stream.ConsumeRandomLengthString();
  
  // The va_list is not directly fuzzable, so we just pass an empty one.
  va_list args;
  va_start(args, format);
  
  // Call the function to be fuzzed
  int ret = pn_data_vfill(pn_data, const_cast<char*>(format.c_str()), reinterpret_cast<__va_list_tag*>(&args));

  // Clean up
  va_end(args);
  pn_data_free(pn_data);

  return 0;
}