#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/SprImpl.h"
}

#include "fuzzer_temp_file.h"

using Alembic::AbcCoreOgawa::v12::SprImpl;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);
  char *ptr = new char[1024];
  SprImpl impl;
  impl.getSample(nullptr, 0, ptr);
  delete[] ptr;

  return 0;
}