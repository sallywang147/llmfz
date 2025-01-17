#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "ck_hash.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  double key = stream.ConsumeFloatingPoint<double>();
  std::string value = stream.ConsumeRemainingBytesAsString();
  struct ck_hash_table_s *table = ck_hash_init(CK_MD5_HASH, CK_NULL);

  int ret = ck_double_hash_insert(&key, value.c_str(), table);
  ck_hash_destroy(table);
  return ret;
}