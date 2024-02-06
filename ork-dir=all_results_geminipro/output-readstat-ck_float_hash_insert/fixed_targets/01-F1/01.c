#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <ck_hash.h>
}

#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const float key = stream.ConsumeFloatingPoint<float>();
  const std::string value = stream.ConsumeRemainingBytesAsString();
  ck_hash_t* table = ck_hash_init(CK_MD5_HASH);

  int ret = ck_float_hash_insert(key, const_cast<char*>(value.c_str()), table);
  ck_hash_destroy(table);
  return ret;
}