#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mail_conf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the fuzzer.
  FuzzedDataProvider provider(data, size);

  // Read the configuration file.
  char* config_file = provider.ConsumeRandomLengthString().c_str();
  mail_conf_read(config_file);

  // Free the configuration file.
  free(config_file);

  return 0;
}