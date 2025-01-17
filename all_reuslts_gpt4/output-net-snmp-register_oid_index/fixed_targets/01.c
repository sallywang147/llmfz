#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "net-snmp/net-snmp-config.h"
#include "net-snmp/net-snmp-includes.h"
#include "net-snmp/agent/net-snmp-agent-includes.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  const size_t name_len = provider.ConsumeIntegralInRange<size_t>(0, size / 2);
  const size_t value_len = provider.ConsumeIntegralInRange<size_t>(0, size - name_len);

  std::vector<size_t> name = provider.ConsumeIntegralVector<size_t>(name_len);
  std::vector<size_t> value = provider.ConsumeIntegralVector<size_t>(value_len);

  struct variable_list *vl = register_oid_index(name.data(), name_len, value.data(), value_len);

  if (vl) {
    snmp_free_var(vl);
  }

  return 0;
}