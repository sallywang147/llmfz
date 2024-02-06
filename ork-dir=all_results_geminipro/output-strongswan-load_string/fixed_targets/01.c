#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private_settings.h"

extern "C" {
#include "load_string.h"  // Include the necessary header file for the declaration of `load_string`.
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  struct private_settings_t *this_ = new private_settings_t;
  size_t settings_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char *settings = new char[settings_size + 1];
  provider.ConsumeBytes(settings, settings_size);
  settings[settings_size] = '\0';
  bool merge = provider.ConsumeBool();
  bool ret = load_string(this_, settings, merge);
  delete[] settings;
  delete this_;
  return 0;
}