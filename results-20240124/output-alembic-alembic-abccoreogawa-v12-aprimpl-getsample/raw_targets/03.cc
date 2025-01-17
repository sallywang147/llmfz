 #include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "alembic/lib/Alembic/AbcCoreAbstract/All.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"

#include "fuzzer_temp_file.h"

using Alembic::AbcCoreAbstract::ArchiveInfo;
using Alembic::AbcCoreAbstract::ReadArraySampleCachePtr;
using Alembic::AbcCoreAbstract::ReadObjectHeaderPtr;
using Alembic::AbcCoreOgawa::v12::AprImpl;
using Alembic::AbcCoreOgawa::v12::OgawaArchive;
using Alembic::AbcCoreOgawa::v12::OgawaDataPtr;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);

  OgawaArchive archive;
  ArchiveInfo archiveInfo;
  archiveInfo.setArchive(tempFile.filename());
  archive.open(archiveInfo);

  if (archive.valid()) {
    const ReadObjectHeaderPtr header = archive.getTop();
    std::shared_ptr<ReadArraySampleCachePtr> cache;
    AprImpl::getSample(header.get(), 0, &cache);
  }

  return 0;
}