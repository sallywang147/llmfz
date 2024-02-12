#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "alembic/lib/Alembic/AbcCoreAbstract/All.h"

extern "C" {
#include "alembic/lib/Alembic/AbcCoreOgawa/ReadUtil.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::shared_ptr<Alembic::AbcCoreOgawa::v12::IData> odata;
  std::shared_ptr<Alembic::AbcCoreAbstract::v12::ArraySample> array;
  Alembic::AbcCoreAbstract::v12::DataType dtype;
  std::shared_ptr<Alembic::AbcCoreOgawa::v12::IData> odata2;

  Alembic::AbcCoreOgawa::v12::ReadArraySample(&odata, &array, size, &dtype,
                                               &odata2);

  return 0;
}