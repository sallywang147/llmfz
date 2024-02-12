#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern "C" {
#include "alembic/lib/Alembic/Abc/All.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
}

#include "fuzzer_temp_file.h"

using Alembic::Abc::GetArchiveInfo;
using Alembic::Abc::ObjectReaderPtr;
using Alembic::AbcCoreOgawa::v12::AprImpl;
using Alembic::AbcCoreOgawa::v12::ReadArchive;
using Alembic::AbcCoreOgawa::v12::ReadDataPtr;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);

  ReadArchive archive;
  GetArchiveInfo archiveInfo;
  archiveInfo.set(tempFile.filename());
  archive.open(archiveInfo);

  if (archive.valid()) {
    const ObjectReaderPtr header = archive.getTop();
    std::shared_ptr<ReadDataPtr> cache;
    AprImpl::getSample(header.get(), 0, &cache);
  }

  return 0;
}