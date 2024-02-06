#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "shl_htable.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct shl_htable *htable = shl_htable_new();
  if (!htable) {
    return 0;
  }

  std::string obj = stream.ConsumeRandomLengthString();
  size_t hash = stream.ConsumeIntegral<size_t>();

  int result = shl_htable_insert(htable, const_cast<char*>(obj.c_str()), hash);

  shl_htable_free(htable);

  return 0;
}