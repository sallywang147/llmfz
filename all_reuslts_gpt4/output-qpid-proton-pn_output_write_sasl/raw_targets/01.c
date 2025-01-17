#include <fuzzer/FuzzedDataProvider.h>
#include <proton/transport.h>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct pn_transport_t *transport = pn_transport();
  if (transport == nullptr) {
    return 0;
  }

  int sasl = stream.ConsumeIntegral<int>();
  size_t bufferSize = stream.remaining_bytes();
  std::string buffer = stream.ConsumeRemainingBytesAsString();

  pn_output_write_sasl(transport, sasl, buffer.data(), bufferSize);

  pn_transport_free(transport);

  return 0;
}