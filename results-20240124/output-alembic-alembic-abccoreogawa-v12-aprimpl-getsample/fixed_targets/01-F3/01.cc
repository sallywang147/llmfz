#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/AprImpl.h"

#include "fuzzer_temp_file.h"

using namespace Alembic::AbcCoreOgawa::v12;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);
  int fd = open(tempFile.filename(), O_RDONLY);
  if (fd < 0) {
    err(EXIT_FAILURE, "open");
  }
  Ogawa::ReadData readData(fd);
  Ogawa::DataHeader dataHeader;
  dataHeader.read(readData);
  AprImpl aprImpl(dataHeader, readData);
  std::shared_ptr<Ogawa::CprData> cprData;
  aprImpl.getSample(0, &cprData);
  close(fd);

  return 0;
}