#include <fuzzer/FuzzedDataProvider.h>

void reload_routing_script() {
  // Implement the function here.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  reload_routing_script();
  return 0;
}