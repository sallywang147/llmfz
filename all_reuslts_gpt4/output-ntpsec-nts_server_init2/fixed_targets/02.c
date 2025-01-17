#include <cstddef>
#include <cstdint>

extern bool nts_server_init2();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function nts_server_init2() does not take any arguments, we do not need to use the input data for anything.
  // Simply call the function.
  bool result = nts_server_init2();

  // We return 0 as per the LLVMFuzzerTestOneInput function requirements.
  return 0;
}