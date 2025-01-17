#include <jsoncons/json.hpp>
#include <jsoncons/json_cursor.hpp>
#include <jsoncons/json_reader.hpp>
#include <jsoncons_ext/csv/csv.hpp>
#include <stdio.h>

using namespace jsoncons;
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, std::size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  json_reader reader(input);
  json_cursor cursor(reader);
  basic_staj_cursor visitor;
  std::error_code ec;
  cursor.read_to(&visitor, &ec);
  return 0;
}