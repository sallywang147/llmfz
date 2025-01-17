#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "shl_htable.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct shl_htable_int ht;
  shl_htable_int_init(&ht);

  while (stream.remaining_bytes() > 0) {
    size_t hash = stream.ConsumeIntegral<size_t>();
    std::string p = stream.ConsumeRandomLengthString();
    htable_add(&ht, hash, const_cast<char*>(p.c_str()));
  }

  shl_htable_int_clear(&ht);

  return 0;
}