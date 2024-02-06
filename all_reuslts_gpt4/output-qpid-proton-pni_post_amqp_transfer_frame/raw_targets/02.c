#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "proton/pn_transport.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a pn_transport_t object
  struct pn_transport_t *transport = pn_transport();
  if(!transport) {
    return 0;
  }

  // Extract integral values
  short short_arg = stream.ConsumeIntegral<short>();
  int int_arg1 = stream.ConsumeIntegral<int>();
  int int_arg2 = stream.ConsumeIntegral<int>();
  size_t size_arg1 = stream.ConsumeIntegral<size_t>();
  int int_arg3 = stream.ConsumeIntegral<int>();
  size_t size_arg2 = stream.ConsumeIntegral<size_t>();

  // Extract boolean values
  bool bool_arg1 = stream.ConsumeBool();
  bool bool_arg2 = stream.ConsumeBool();
  bool bool_arg3 = stream.ConsumeBool();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeRandomLengthString();
  char *char_ptr = const_cast<char*>(str.c_str());

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
  struct pn_bytes_t bytes_struct = {bytes.size(), reinterpret_cast<char*>(bytes.data())};

  // Create a pn_data_t object
  struct pn_data_t *data_arg = pn_data(0);
  if(!data_arg) {
    pn_transport_free(transport);
    return 0;
  }

  // Call the function to fuzz
  int result = pni_post_amqp_transfer_frame(transport, short_arg, int_arg1, int_arg2, &bytes_struct, size_arg1, char_ptr, bool_arg1, bool_arg2, int_arg3, size_arg2, data_arg, bool_arg3);

  // Free the resources
  pn_data_free(data_arg);
  pn_transport_free(transport);

  return 0;
}