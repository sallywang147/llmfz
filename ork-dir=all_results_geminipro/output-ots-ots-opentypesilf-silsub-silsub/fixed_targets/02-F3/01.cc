#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"
#include "ots.h"

namespace {

class SILSub : public ots::OpenTypeSILF::SILSub {
 public:
  using namespace ots;  // Add this line to use the ots namespace.

  SILSub() {}
  ~SILSub() {}

  bool Parse(Buffer *buf, OpenTypeFile *font) override {
    return true;
  }
  bool Serialize(Buffer *buf, OpenTypeFile *font) override {
    return true;
  }
};

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  SILSub sub;
  Buffer buf(data, size);
  sub.Parse(&buf, nullptr);
  sub.Serialize(&buf, nullptr);
  return 0;
}