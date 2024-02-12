#include <boost/json.hpp>
#include <stddef.h>

extern "C" {
#include "Fuzzer.h"
}

size_t LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  boost::json::value v;
  boost::json::parse(&v, (char *)data, size);
  return 0;
}