#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"

namespace ots {

class SILSub;

class SILPass {
 public:
  SILPass() {}
  void SILPass(SILPass*, SILPass*) {}
};

}  // namespace ots

extern "C" {
#include "opentype-sanitiser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::OpenTypeSILF::SILSub::SILPass pass;
  pass.SILPass(nullptr, nullptr);
  return 0;
}