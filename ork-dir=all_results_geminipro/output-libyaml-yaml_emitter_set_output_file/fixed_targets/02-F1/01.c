#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);
  yaml_emitter_set_output_file(&emitter, stdout);
  std::string text = stream.ConsumeRemainingBytesAsString();
  yaml_emitter_dump(&emitter, reinterpret_cast<const uint8_t*>(text.c_str()),
                    text.size());
  yaml_emitter_delete(&emitter);
  return 0;
}