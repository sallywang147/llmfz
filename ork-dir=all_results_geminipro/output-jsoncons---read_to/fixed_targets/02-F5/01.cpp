#include <jsoncons/json.hpp>
#include <stdio.h>

using namespace jsoncons;

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, std::size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  json_reader reader(input);
  jsoncons::basic_json_cursor<char, jsoncons::stream_source<char>, std::__1::allocator<char> > cursor(reader);
  jsoncons::basic_staj_cursor visitor;
  std::error_code ec;
  try {
    cursor.read_to(&visitor, &ec);
  } catch (const std::exception& e) {
    fprintf(stderr, "Error: %s\n", e.what());
    return 1;
  }
  if (ec) {
    fprintf(stderr, "Error: %s\n", ec.message().c_str());
    return 1;
  }
  return 0;
}
}