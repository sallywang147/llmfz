#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "proton/pn_transport.h"

extern "C" {
#include "proton/pn_transport.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const char *sasl_cmd = stream.ConsumeRandomLengthString().c_str();
  const size_t sasl_cmd_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  size_t bytes_written = pn_output_write_sasl(nullptr, fd,
                                              const_cast<char*>(sasl_cmd),
                                              sasl_cmd_len);
  return 0;
}