#include <stddef.h>
#include <stdint.h>

#include "opentype-sanitiser.h"
#include "ots-memory-stream.h"
#include "ots.h"

namespace {

class SILPass : public ots::OpenTypeSILF::SILSub::SILPass {
public:
  SILPass() {}
  bool Run(ots::OpenTypeSILF::Buffer *buffer,
           ots::OpenTypeFILE *font_file) override {
    return true;
  }
};

} // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  ots::OpenTypeSILF::Buffer buffer;
  buffer.data = data;
  buffer.length = size;

  ots::OpenTypeFILE file;
  file.buffer = &buffer;
  file.read_only = true;

  SILPass pass;
  pass.Run(&buffer, &file);

  return 0;
}