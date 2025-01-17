#include <stddef.h>
#include <stdint.h>
#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"
#include "ots.h"

namespace ots {

struct SILSub {
  SILSub() {}
  void SILSub(SILSub *other) {}
};

class OpenTypeSILF {
 public:
  OpenTypeSILF() {}
  bool Parse(const uint8_t *data, size_t length) {
    ots::ExpandingMemoryStream stream(length /*initial*/, length * 8 /*limit*/);
    stream.WriteRaw(data, length);
    stream.Seek(0);
    bool ok = ots::OpenTypeSILF::Deserialize(&stream, this);
    return ok;
  }

  std::vector<SILSub> subs;
};

}  // namespace ots

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::OpenTypeSILF silf;
  if (!silf.Parse(data, size)) {
    return 0;
  }
  for (size_t i = 0; i < silf.subs.size(); ++i) {
    for (size_t j = 0; j < silf.subs.size(); ++j) {
      silf.subs[i].SILSub(&silf.subs[j]);
    }
  }
  return 0;
}