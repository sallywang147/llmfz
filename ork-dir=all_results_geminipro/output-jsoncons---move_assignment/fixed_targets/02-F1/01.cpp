#include <jsoncons/json.hpp>

using namespace jsoncons;

extern "C" {
int LLVMFuzzerTestOneInput(const uint8_t *data, std::size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  json j1 = json::parse(input);
  json j2 = json::parse(input);
  j1.move_assignment(&j2);
  return 0;
}
}