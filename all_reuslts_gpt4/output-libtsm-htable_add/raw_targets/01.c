#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "shl_htable.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct shl_htable_int ht;
  shl_htable_int_init(&ht, NULL, NULL);

  size_t hash = stream.ConsumeIntegral<size_t>();
  std::string str = stream.ConsumeRemainingBytesAsString();
  char* p = const_cast<char*>(str.c_str());

  htable_add(&ht, hash, p);

  shl_htable_int_clear(&ht);

  return 0;
}