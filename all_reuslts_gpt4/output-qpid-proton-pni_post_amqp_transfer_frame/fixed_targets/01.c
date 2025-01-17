#include <fuzzer/FuzzedDataProvider.h>
#include <proton/types.h>
#include <proton/transport.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Proton library
  pn_transport_t *transport = pn_transport();

  // Extract integral values
  short short_arg = stream.ConsumeIntegral<short>();
  int int_arg1 = stream.ConsumeIntegral<int>();
  int int_arg2 = stream.ConsumeIntegral<int>();
  int int_arg3 = stream.ConsumeIntegral<int>();
  size_t size_arg1 = stream.ConsumeIntegral<size_t>();
  size_t size_arg2 = stream.ConsumeIntegral<size_t>();

  // Extract boolean values
  bool bool_arg1 = stream.ConsumeBool();
  bool bool_arg2 = stream.ConsumeBool();
  bool bool_arg3 = stream.ConsumeBool();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *char_ptr = const_cast<char*>(str.c_str());

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  size_t byte_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(byte_size);
  pn_bytes_t pn_bytes = {byte_size, reinterpret_cast<char*>(bytes.data())};

  // Prepare a pn_data_t object
  pn_data_t *pn_data = pn_data(0);

  // Call the function to fuzz
  pni_post_amqp_transfer_frame(transport, short_arg, int_arg1, int_arg2, &pn_bytes, size_arg1, char_ptr, bool_arg1, bool_arg2, int_arg3, size_arg2, pn_data, bool_arg3);

  // Cleanup
  pn_data_free(pn_data);
  pn_transport_free(transport);

  return 0;
}