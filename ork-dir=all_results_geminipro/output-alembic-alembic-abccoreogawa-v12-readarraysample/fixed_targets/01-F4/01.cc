#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "AbcCoreOgawa/v12/ReadArraySample.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  auto i_dims = std::make_shared<std::vector<size_t>>();
  auto i_data = std::make_shared<std::vector<uint8_t>>();
  auto data_type = std::make_shared<Alembic::AbcCoreAbstract::v12::DataType>(
      Alembic::AbcCoreAbstract::v12::DataType::kUnknown);
  auto i_child_bounds = std::make_shared<std::vector<Alembic::AbcCoreAbstract::v12::ArraySample>>();
  Alembic::AbcCoreOgawa::v12::ReadArraySample(i_dims, i_data, 0, data_type, i_child_bounds);
  return 0;
}