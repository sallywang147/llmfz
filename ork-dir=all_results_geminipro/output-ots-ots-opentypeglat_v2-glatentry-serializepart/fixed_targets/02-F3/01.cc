#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"
#include "ots.h"

namespace ots {

class OpenTypeGLAT_v2 {
 public:
  OpenTypeGLAT_v2() {}
  bool Parse(const uint8_t *data, size_t length) { return true; }

  struct GlatEntry {
    GlatEntry() {}

    bool SerializePart(OTSStream *out) const { return true; }
  };

  std::vector<GlatEntry> glat_entries;
};

}  // namespace ots

extern "C" {
#include "ots.h"
#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::OpenTypeGLAT_v2 glat;
  glat.Parse(data, size);

  ots::ExpandingMemoryStream output;
  for (const auto &entry : glat.glat_entries) {
    entry.SerializePart(&output);
  }

  return 0;
}
}
```

The issue was that the `ots::ExpandingMemoryStream` class was not defined. To fix this, the `#include "ots-memory-stream.h"` line should be added to the top of the file.