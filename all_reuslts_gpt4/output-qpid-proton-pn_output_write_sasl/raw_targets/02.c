#include <fuzzer/FuzzedDataProvider.h>
#include <proton/transport.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a transport object
  pn_transport_t *transport = pn_transport();

  // Consume data from the fuzzing input
  int arg2 = stream.ConsumeIntegral<int>();
  std::string arg3 = stream.ConsumeRandomLengthString();
  size_t arg4 = arg3.size();

  // Call the function to fuzz
  pn_output_write_sasl(transport, arg2, &arg3[0], arg4);

  // Free the transport object
  pn_transport_free(transport);

  return 0;
}