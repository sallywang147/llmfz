#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "proton/pn_transport.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const char *sasl_cmd = stream.ConsumeRandomLengthString().c_str();
  const size_t sasl_cmd_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  pn_transport_t *transport = pn_transport();
  size_t bytes_written = pn_output_write_sasl(transport, fd,
                                              const_cast<char*>(sasl_cmd),
                                              sasl_cmd_len);
  pn_transport_free(transport);
  return 0;
}