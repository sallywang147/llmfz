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

using Alembic::AbcCoreOgawa::v12::AprImpl;
using Alembic::AbcCoreOgawa::v12::CprImpl;
using Alembic::AbcCoreOgawa::v12::DataHeader;
using Alembic::AbcCoreOgawa::v12::ReadData;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);
  int fd = open(tempFile.filename(), O_RDONLY);
  if (fd < 0) {
    err(EXIT_FAILURE, "open");
  }
  ReadData readData(fd);
  DataHeader dataHeader;
  dataHeader.read(readData);
  AprImpl aprImpl;
  aprImpl.init(dataHeader, readData);
  std::shared_ptr<CprImpl> cprImpl;
  aprImpl.getSample(0, &cprImpl);
  close(fd);

  return 0;
}