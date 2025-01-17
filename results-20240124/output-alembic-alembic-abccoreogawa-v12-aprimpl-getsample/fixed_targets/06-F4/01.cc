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
#include "alembic/lib/Alembic/AbcCoreOgawa/CprImpl.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/Foundation.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/OgawaUtil.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/ReadUtil.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/StreamManager.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/WriteUtil.h"

#include "fuzzer_temp_file.h"

using Alembic::AbcCoreOgawa::v12::AprImpl;
using Alembic::AbcCoreOgawa::v12::CprImpl;
using Alembic::AbcCoreOgawa::v12::Foundation;
using Alembic::AbcCoreOgawa::v12::OgawaIndex;
using Alembic::AbcCoreOgawa::v12::OgawaUtil;
using Alembic::AbcCoreOgawa::v12::ReadUtil;
using Alembic::AbcCoreOgawa::v12::StreamManager;
using Alembic::AbcCoreOgawa::v12::WriteUtil;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);
  std::string fileName = tempFile.filename();

  // Open the file.
  int fd = open(fileName.c_str(), O_RDONLY);
  if (fd == -1) {
    err(1, "Could not open file %s: %s", fileName.c_str(),
        strerror(errno));
  }

  // Create the stream manager.
  StreamManager streamManager;
  streamManager.initializeFromExistingFile(fd);

  // Create the index.
  OgawaIndex index(streamManager);

  // Get the CPR.
  CprImpl cpr(streamManager, index);

  // Get the APR.
  AprImpl apr(streamManager, index, cpr);

  // Get the sample.
  std::shared_ptr<void> sample;
  apr.getSample(0, &sample);

  // Close the file.
  close(fd);

  return 0;
}