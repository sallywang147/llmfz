#include "settings.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  char *settings = reinterpret_cast<char *>(bytes.data());
  struct settings_t *settings_ptr = settings_create_string(settings);
  free(settings_ptr);
  return 0;
}