#include <fuzzer/FuzzedDataProvider.h>
#include <yaml.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  yaml_emitter_t emitter;
  yaml_emitter_initialize(&emitter);

  int indent = stream.ConsumeIntegralInRange<int>(0, 10);
  yaml_emitter_set_indent(&emitter, indent);

  yaml_emitter_delete(&emitter);

  return 0;
}