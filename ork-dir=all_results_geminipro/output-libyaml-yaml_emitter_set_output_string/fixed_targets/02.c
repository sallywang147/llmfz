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
  char* output = new char[text.size() + 3]; // Add 3 for the null-terminator
  yaml_emitter_set_output_string(&emitter, output, text.size() + 3, &size_written);
  yaml_emitter_dump(&emitter, reinterpret_cast<const unsigned char*>(text.c_str()),
                    text.size());
  yaml_emitter_delete(&emitter);
  output[size_written] = '\0'; // Add the null-terminator
  output[size_written + 1] = '\0'; // Add an extra null-terminator for safety
  output[size_written + 2] = '\0'; // Add another extra null-terminator for safety
  delete[] output;
  return 0;
}
```

The original code had a buffer overflow issue because it allocated a buffer of size `text.size() + 2` for the YAML output, but the YAML emitter may write up to `text.size() + 3` bytes, including the null-terminator. To fix this issue, the buffer size has been increased to `text.size() + 3`. Additionally, two extra null-terminators have been added to the buffer for safety.