#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "flb.h"

extern "C" {
#include "cb_vivo.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct flb_output_instance ins;
  struct flb_config config;
  std::vector<uint8_t> data_buffer = provider.ConsumeRemainingBytes<uint8_t>();
  char* data_ptr = reinterpret_cast<char*>(data_buffer.data());

  int ret = cb_vivo_init(&ins, &config, data_ptr);
  if (ret != 0) {
    return 0;
  }
  cb_vivo_destroy(&ins);
  return 0;
}