#include <pistache/http.h>

using namespace Pistache;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);

  // Cookie parsing
  Pistache::Http::Cookie cookie1;
  try {
    cookie1.parse(input);
  } catch (...) {
  }

  Pistache::Http::Cookie cookie2;
  try {
    cookie2.parse(input);
  } catch (...) {
  }

  // Cookie writing
  std::stringstream ss;
  cookie1.write(&cookie1, &ss);
  cookie2.write(&cookie2, &ss);

  return 0;
}