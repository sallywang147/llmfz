#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <memory>

#include "Alembic/AbcCoreOgawa/ReadArraySample.h"
#include "Alembic/AbcCoreAbstract/DataType.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::shared_ptr<void> iDims = std::make_shared<void>();
  std::shared_ptr<void> iData = std::make_shared<void>();
  std::shared_ptr<void> iHandle = std::make_shared<void>();
  
  Alembic::AbcCoreAbstract::v12::DataType dataType;
  
  Alembic::AbcCoreOgawa::v12::ReadArraySample(&iDims, &iData, stream.ConsumeIntegral<size_t>(), &dataType, &iHandle);

  return 0;
}