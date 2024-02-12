 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "fuzzer_temp_file.h"

using Alembic::AbcCoreAbstract::DataType;
using Alembic::AbcCoreOgawa::ReadArraySample;
using Alembic::AbcCoreOgawa::ReadData;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzerTemporaryFile tempFile(data, size);
  ReadData readData(tempFile.filename());

  std::shared_ptr<std::vector<size_t>> iDims;
  std::shared_ptr<std::vector<uint8_t>> iData;
  DataType dataType;
  std::shared_ptr<std::vector<uint8_t>> iData2;

  ReadArraySample(&iDims, &iData, 0, &dataType, &iData2);

  return 0;
}