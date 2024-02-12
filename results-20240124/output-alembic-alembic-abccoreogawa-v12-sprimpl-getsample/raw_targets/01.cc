 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"

using Alembic::AbcCoreOgawa::v12::SprImpl;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  SprImpl impl;
  impl.getSample(nullptr, size, (char *)data);
  return 0;
}