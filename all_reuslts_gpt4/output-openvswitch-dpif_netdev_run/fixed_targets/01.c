#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dpif-netdev.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  struct dpif dpif;
  
  // Initialize dpif structure with fuzzed data
  dpif.name = stream.ConsumeRandomLengthString().c_str();
  dpif.type = stream.ConsumeRandomLengthString().c_str();
  dpif.max_ufid_hashes = stream.ConsumeIntegral<uint32_t>();
  dpif.port_seq = stream.ConsumeIntegral<uint64_t>();
  dpif.flow_seq = stream.ConsumeIntegral<uint64_t>();
  dpif.dp_seq = stream.ConsumeIntegral<uint64_t>();
  dpif.user_features = stream.ConsumeIntegral<uint32_t>();
  
  dpif_netdev_run(&dpif);

  return 0;
}