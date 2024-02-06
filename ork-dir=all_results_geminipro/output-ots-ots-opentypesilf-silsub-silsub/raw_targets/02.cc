#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"
#include "ots.h"

namespace {

class SILSub : public ots::OpenTypeSILF::SILSub {
 public:
  SILSub() {}
  ~SILSub() {}

  bool Parse(ots::Buffer *buf, ots::OpenTypeFile *font) override {
    return true;
  }
  bool Serialize(ots::Buffer *buf, ots::OpenTypeFile *font) override {
    return true;
  }
};

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  SILSub sub;
  ots::Buffer buf(data, size);
  sub.Parse(&buf, nullptr);
  sub.Serialize(&buf, nullptr);
  return 0;
}