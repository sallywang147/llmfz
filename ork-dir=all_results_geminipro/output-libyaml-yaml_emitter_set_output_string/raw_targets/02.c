#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct yaml_emitter_s emitter;
  yaml_emitter_initialize(&emitter);

  const std::string text = stream.ConsumeRemainingBytesAsString();
  size_t size_written;
  char* output = new char[text.size()];
  yaml_emitter_set_output_string(&emitter, output, text.size(), &size_written);
  yaml_emitter_dump(&emitter, reinterpret_cast<const unsigned char*>(text.c_str()),
                    text.size());
  yaml_emitter_delete(&emitter);
  delete[] output;
  return 0;
}