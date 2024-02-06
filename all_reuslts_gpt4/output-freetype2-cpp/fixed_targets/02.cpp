#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" void _GLOBAL__sub_I_template_cpp();

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // As the function "_GLOBAL__sub_I_template_cpp()" does not take any arguments, we do not need to use FuzzedDataProvider in this case.
  // Simply call the function.
  _GLOBAL__sub_I_template_cpp();
  
  return 0;
}