#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "alembic/lib/Alembic/AbcCoreAbstract/All.h"

extern "C" {
#include "alembic/lib/Alembic/AbcCoreOgawa/ReadUtil.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/IData.h"
#include "alembic/lib/Alembic/AbcCoreOgawa/CAbcOgawaData.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::shared_ptr<Alembic::AbcCoreOgawa::IData> odata;
  std::shared_ptr<Alembic::AbcCoreAbstract::ArraySample> array;
  Alembic::AbcCoreAbstract::DataType dtype;
  std::shared_ptr<Alembic::AbcCoreOgawa::CAbcOgawaData> iodata2;

  Alembic::AbcCoreOgawa::ReadArraySample(&odata, &array, size, &dtype,
                                               &iodata2);

  return 0;
}