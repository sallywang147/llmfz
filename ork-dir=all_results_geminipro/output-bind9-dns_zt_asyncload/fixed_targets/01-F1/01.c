#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "dns.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct dns_zt zt;
  memset(&zt, 0, sizeof(zt));

  const bool newonly = stream.ConsumeBool();
  const char* arg = stream.ConsumeRandomLengthString().c_str();

  const auto func_type_values = {
      [](void* arg) { return 0; },
      [](void* arg) { return 1; },
      [](void* arg) { return 2; }};
  const func_type loaddone = stream.PickValueInArray(func_type_values);

  dns_zt_asyncload(&zt, newonly, loaddone, const_cast<char*>(arg));
  return 0;
}