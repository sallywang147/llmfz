#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "snmp_api.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t name_len = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::vector<size_t> name = stream.ConsumeIntegralVector<size_t>(name_len);

  size_t value_len = stream.ConsumeIntegralInRange<size_t>(0, size / 2);
  std::vector<size_t> value = stream.ConsumeIntegralVector<size_t>(value_len);

  struct variable_list* result = register_oid_index(name.data(), name_len, value.data(), value_len);

  // We don't use the result, but the call is made to fuzz the function.
  return 0;
}