#include <stdint.h>
#include <znc/znc.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string input(reinterpret_cast<const char *>(data), size);
  CZNC znc;
  znc.ParseConfig(input);
  znc.GetConfig();
  return 0;
}