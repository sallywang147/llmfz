#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <yaml.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);

  size_t output_size = stream.remaining_bytes();
  char* output = new char[output_size];
  size_t size_written = 0;

  yaml_emitter_set_output_string(&emitter, output, output_size, &size_written);

  yaml_emitter_delete(&emitter);
  delete[] output;

  return 0;
}