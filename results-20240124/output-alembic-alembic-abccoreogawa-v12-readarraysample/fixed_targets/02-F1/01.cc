#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
}

using Alembic::AbcCoreAbstract::DataType;
using Alembic::AbcCoreAbstract::v12::ReadArraySampleID;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::shared_ptr<int32_t> iDims;
  std::shared_ptr<int32_t> iData;
  std::shared_ptr<int32_t> iData2;
  DataType dataType;
  ReadArraySampleID(&iDims, &iData, size, &dataType, &iData2);
  return 0;
}