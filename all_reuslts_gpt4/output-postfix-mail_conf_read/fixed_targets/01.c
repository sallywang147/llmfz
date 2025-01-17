#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "mail_conf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function mail_conf_read() doesn't take any arguments, we don't need to use FuzzedDataProvider in this case.
  // Simply call the function.
  mail_conf_read();

  return 0;
}