#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" {
#include "proton/pn_config.h"
#include "proton/pn_transport.h"
}

extern "C" size_t LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const char* buffer = stream.ConsumeBytesAsString().c_str();
  const size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct pn_transport_t* transport = pn_transport();
  size_t result = pn_transport_output_write_sasl(transport, fd, const_cast<char*>(buffer),
                                       buffer_size);
  pn_free(transport);
  return result;
}
```

The fix is to change the function name `pn_transport_output_write_sasl` to `pn_transport_output_write_sasl`.