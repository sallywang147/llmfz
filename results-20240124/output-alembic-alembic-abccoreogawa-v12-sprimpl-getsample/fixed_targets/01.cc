#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"

extern "C" {
#include "alembic/lib/Alembic/AbcCoreOgawa/SprImpl.h"
}

using Alembic::AbcCoreOgawa::v12::SprImpl;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  SprImpl impl(nullptr, nullptr, nullptr);
  impl.getSample(0, (char *)data);
  return 0;
}