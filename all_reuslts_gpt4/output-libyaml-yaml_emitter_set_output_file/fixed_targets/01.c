#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "yaml.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  yaml_emitter_t emitter;
  if (!yaml_emitter_initialize(&emitter)) {
    return 0;
  }

  FILE *fp = tmpfile();
  if (fp == NULL) {
    yaml_emitter_delete(&emitter);
    return 0;
  }

  yaml_emitter_set_output_file(&emitter, fp);

  yaml_emitter_delete(&emitter);
  fclose(fp);

  return 0;
}