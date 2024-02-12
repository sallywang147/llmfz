 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"

using Alembic::AbcCoreAbstract::DataType;
using Alembic::AbcCoreOgawa::v12::ReadArraySample;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::shared_ptr<int32_t> iDims;
  std::shared_ptr<int32_t> iData;
  std::shared_ptr<int32_t> iData2;
  DataType dataType;
  ReadArraySample(&iDims, &iData, size, &dataType, &iData2);
  return 0;
}