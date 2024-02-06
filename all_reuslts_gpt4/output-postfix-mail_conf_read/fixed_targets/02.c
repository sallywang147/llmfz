#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "mail_conf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

  // Since mail_conf_read() does not take any parameters, we do not need to use FuzzedDataProvider.
  // However, we need to ensure that the environment is properly set up for the function to run.
  // This may involve setting up configuration files, environment variables, etc.
  // For the purpose of this example, we will assume that such setup is not required.

  // Call the function to fuzz
  mail_conf_read();

  return 0;
}