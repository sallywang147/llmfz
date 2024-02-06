#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  yaml_emitter_t emitter;
  if (!yaml_emitter_initialize(&emitter)) {
    return 0;
  }

  const int indent = stream.ConsumeIntegral<int>();
  yaml_emitter_set_indent(&emitter, indent);

  yaml_emitter_delete(&emitter);
  return 0;
}