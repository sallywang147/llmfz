#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "yaml.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string file_name = stream.ConsumeRemainingBytesAsString();
  FILE* file = fopen(file_name.c_str(), "w");
  if (file == nullptr) {
    return 0;
  }

  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);
  yaml_emitter_set_output_file(&emitter, file);
  yaml_emitter_flush(&emitter);  // Add this line to flush the output buffer.
  yaml_emitter_delete(&emitter);
  fclose(file);
  return 0;
}