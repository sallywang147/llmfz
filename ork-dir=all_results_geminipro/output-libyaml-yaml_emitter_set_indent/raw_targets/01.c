#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int indent = stream.ConsumeIntegral<int>();
  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);
  yaml_emitter_set_indent(&emitter, indent);
  yaml_emitter_delete(&emitter);
  return 0;
}