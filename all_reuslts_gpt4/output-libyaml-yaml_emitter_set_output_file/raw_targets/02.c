#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);

  // Create a temporary file for the emitter to write to.
  FILE* file = tmpfile();
  if (!file) {
    yaml_emitter_delete(&emitter);
    return 0;
  }

  yaml_emitter_set_output_file(&emitter, file);

  // Clean up.
  fclose(file);
  yaml_emitter_delete(&emitter);

  return 0;
}