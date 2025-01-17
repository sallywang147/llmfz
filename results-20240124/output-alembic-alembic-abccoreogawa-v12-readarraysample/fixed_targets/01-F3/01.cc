#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "alembic/lib/Alembic/AbcCoreAbstract/All.h"

#include "fuzzer_temp_file.h"

using Alembic::AbcCoreAbstract::ArraySample;
using Alembic::AbcCoreAbstract::DataType;
using Alembic::AbcCoreAbstract::Dimensions;
using Alembic::AbcCoreAbstract::ReadArraySampleID;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);

  std::shared_ptr<Dimensions> iDims;
  std::shared_ptr<ArraySample> iData;
  std::shared_ptr<DataType> iDataType;
  std::shared_ptr<ArraySample> oData;
  ReadArraySampleID(0, &iDims, &iData, &iDataType, &oData);

  return 0;
}