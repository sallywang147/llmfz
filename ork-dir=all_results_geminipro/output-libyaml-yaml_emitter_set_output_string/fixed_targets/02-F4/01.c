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
  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);

  const std::string text = stream.ConsumeRemainingBytesAsString();
  size_t size_written;
  char* output = new char[text.size() + 2]; // Add 2 for the null-terminator
  yaml_emitter_set_output_string(&emitter, output, text.size() + 2, &size_written);
  yaml_emitter_dump(&emitter, reinterpret_cast<const unsigned char*>(text.c_str()),
                    text.size());
  yaml_emitter_delete(&emitter);
  output[size_written] = '\0'; // Add the null-terminator
  output[size_written + 1] = '\0'; // Add an extra null-terminator for safety
  delete[] output;
  return 0;
}