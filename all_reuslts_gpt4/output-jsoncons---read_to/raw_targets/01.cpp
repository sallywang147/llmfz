#include <fuzzer/FuzzedDataProvider.h>
#include <jsoncons/json_cursor.hpp>
#include <jsoncons/json.hpp>
#include <jsoncons/json_reader.hpp>
#include <jsoncons/staj_cursor.hpp>
#include <jsoncons/json_staj_cursor.hpp>
#include <jsoncons/staj_reader.hpp>
#include <jsoncons/source.hpp>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string json_str = stream.ConsumeRemainingBytesAsString();
  std::istringstream iss(json_str);
  jsoncons::stream_source<char> source(iss);
  jsoncons::json_cursor<jsoncons::stream_source<char>> cursor(source);

  jsoncons::json j;
  jsoncons::json_staj_cursor jc(j);
  std::error_code ec;

  cursor.read_to(&jc, &ec);

  return 0;
}