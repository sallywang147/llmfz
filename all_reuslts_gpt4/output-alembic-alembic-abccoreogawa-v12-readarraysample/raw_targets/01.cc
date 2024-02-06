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

  std::shared_ptr<int> iDims = std::make_shared<int>(stream.ConsumeIntegral<int>());
  std::shared_ptr<int> iData = std::make_shared<int>(stream.ConsumeIntegral<int>());
  size_t size_arg = stream.ConsumeIntegral<size_t>();
  Alembic::AbcCoreAbstract::v12::DataType dataType;
  std::shared_ptr<int> shared_ptr_arg = std::make_shared<int>(stream.ConsumeIntegral<int>());

  Alembic::AbcCoreOgawa::v12::ReadArraySample(&iDims, &iData, size_arg, &dataType, &shared_ptr_arg);

  return 0;
}