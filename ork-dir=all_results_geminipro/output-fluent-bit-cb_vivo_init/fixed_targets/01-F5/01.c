#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "flb.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct flb_output_instance ins;
  struct flb_config config;
  const std::string data_str = stream.ConsumeRemainingBytesAsString();
  char* data_ptr = const_cast<char*>(data_str.c_str());

  cb_vivo_init(&ins, &config, data_ptr);
  cb_vivo_destroy(&ins);  // Call cb_vivo_destroy to clean up resources
  return 0;
}