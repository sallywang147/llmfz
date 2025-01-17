#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "iec61850_server.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int bufPos = stream.ConsumeIntegral<int>();
  bool encode = stream.ConsumeBool();

  std::vector<char> buffer = stream.ConsumeRemainingBytes<char>();

  MmsValue* value = MmsValue_newEmptyStruct(1);
  if (value == NULL) {
    return 0;
  }

  encodeStructuredAccessResult(value, buffer.data(), bufPos, encode);

  MmsValue_delete(value);

  return 0;
}