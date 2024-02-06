#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "parse.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct parse p;
  p.next = stream.ConsumeIntegral<uint8_t>();
  p.end = stream.ConsumeIntegral<uint8_t>();
  p.error = stream.ConsumeIntegral<uint8_t>();
  p.left = stream.ConsumeIntegral<uint8_t>();
  p.len = stream.ConsumeIntegral<uint8_t>();
  p.ptr = stream.ConsumeRandomLengthString().c_str();

  nonnewline(&p);

  return 0;
}