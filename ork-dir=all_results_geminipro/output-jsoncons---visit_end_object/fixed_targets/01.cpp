#include <fuzzer/FuzzedDataProvider.h>
#include <jsoncons.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  jsoncons::json_decoder<jsoncons::basic_json<char, jsoncons::order_preserving_policy, std::__1::allocator<char> >, std::__1::allocator<char> > decoder;
  std::exception* exception = nullptr;
  std::error_code* error_code = nullptr;
  const std::string json_string = stream.ConsumeRemainingBytesAsString();
  decoder.parse_string(json_string, exception, error_code);
  decoder.visit_end_object(nullptr, exception, error_code); // Call visit_end_object to clean up decoder state
  return 0;
}