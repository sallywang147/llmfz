#include <stddef.h>
#include <stdint.h>
#include <string>

struct Archive {
  void CheckArc(bool EnableBroken);
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  Archive Arc;
  Arc.CheckArc(false);
  return 0;
}