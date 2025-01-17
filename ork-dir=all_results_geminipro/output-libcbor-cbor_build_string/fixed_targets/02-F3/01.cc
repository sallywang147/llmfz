#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "cbor.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "cbor.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);

  std::string str = provider.ConsumeRandomLengthString();
  char *val = str.c_str();
  struct cbor_item_t *item = cbor_build_string(val);
  if (item) {
    cbor_decref(&item);
  }
  return 0;
}