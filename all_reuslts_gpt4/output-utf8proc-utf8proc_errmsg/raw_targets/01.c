#include <utf8proc.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume the data to generate the input
  size_t error_code = stream.ConsumeIntegral<size_t>();

  // Call the function with the fuzzed input
  char * error_message = utf8proc_errmsg(error_code);

  return 0;
}