#include <fuzzer/FuzzedDataProvider.h>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpointer/jsonpointer.hpp>
#include <jsoncons_ext/jsonpatch/jsonpatch.hpp>
#include <exception>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  jsoncons::json_decoder<jsoncons::basic_json<char, jsoncons::order_preserving_policy, std::allocator<char> >, std::allocator<char> > decoder;
  std::exception ex;
  std::error_code ec;
  
  try {
    auto json_string = stream.ConsumeRandomLengthString();
    jsoncons::json::parse(json_string);
    decoder.visit_end_object(&ex, &ec);
  } catch (...) {
    // Ignore all exceptions
  }

  return 0;
}