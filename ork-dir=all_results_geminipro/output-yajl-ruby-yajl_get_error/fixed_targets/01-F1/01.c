#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "api/yajl_parse.h"

extern "C" {
#include "api/yajl_gen.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    yajl_init();
    initialized = true;
  }
  int ret;
  yajl_handle handle = yajl_alloc(NULL, NULL, NULL, NULL);
  if (handle == nullptr) {
    return 0;
  }

  ret = yajl_parse(handle, data, size);
  if (ret == YAJL_OK || ret == YAJL_INCOMPLETE) {
    yajl_free(handle);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> json_text(provider.ConsumeIntegralInRange<size_t>(
      0, provider.remaining_bytes()));
  provider.ConsumeBytes<unsigned char>(json_text.data(), json_text.size());
  std::vector<uint8_t> error_text(provider.ConsumeIntegralInRange<size_t>(
      0, provider.remaining_bytes()));
  provider.ConsumeBytes<unsigned char>(error_text.data(), error_text.size());

  char* error_string = yajl_get_error(handle, provider.ConsumeBool(),
                                      (char*)json_text.data(), json_text.size());
  if (error_string != nullptr) {
    free(error_string);
  }

  yajl_free(handle);

  return 0;
}