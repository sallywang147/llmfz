 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "alembic/lib/Alembic/AbcCoreAbstract/All.h"

using Alembic::AbcCoreAbstract::v12::DataType;
using Alembic::AbcCoreOgawa::v12::ReadArraySample;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::shared_ptr<std::vector<index_t>> iDims;
  std::shared_ptr<std::vector<uint8_t>> iData;
  std::shared_ptr<DataType> iDataType;
  std::shared_ptr<std::vector<std::string>> iNames;

  ReadArraySample(&iDims, &iData, size, &iDataType, &iNames);

  return 0;
}