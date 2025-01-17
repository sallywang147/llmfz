#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "yaml.h"

extern "C" {
#include <yaml.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int indent = stream.ConsumeIntegral<int>();
  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);
  yaml_emitter_set_output(&emitter, NULL);  // Set output to NULL to avoid memory leak
  yaml_emitter_set_indent(&emitter, indent);
  yaml_emitter_delete(&emitter);
  return 0;
}
```

The original code has a memory leak issue because the output of the emitter is not set to NULL. This can be fixed by adding `yaml_emitter_set_output(&emitter, NULL);` before `yaml_emitter_set_indent(&emitter, indent);`.