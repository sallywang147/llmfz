#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fuzzer/FuzzedDataProvider.h>
#include <string>
#include <vector>

#include "alembic/lib/Alembic/AbcCoreOgawa/All.h"
#include "alembic/lib/Alembic/AbcCoreAbstract/All.h"

using Alembic::AbcCoreAbstract::DataType;
using Alembic::AbcCoreAbstract::Dimensions;
using Alembic::AbcCoreOgawa::ReadArraySampleID;
using Alembic::AbcCoreOgawa::ReadDimensions;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::shared_ptr<Dimensions> dims =
      ReadDimensions(stream.ConsumeRemainingBytes<uint8_t>());
  std::shared_ptr<DataType> dtype =
      std::make_shared<DataType>(static_cast<DataType::EnumType>(
          stream.ConsumeIntegralInRange<uint32_t>(0, 10)));
  std::shared_ptr<void> data_ptr;
  std::shared_ptr<void> sample_ptr;

  ReadArraySampleID(dims.get(), &data_ptr, 0, dtype.get(), &sample_ptr);
  return 0;
}