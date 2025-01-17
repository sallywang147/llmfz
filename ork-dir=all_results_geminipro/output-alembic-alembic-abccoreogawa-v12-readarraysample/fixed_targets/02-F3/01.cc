#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "Alembic/AbcCoreAbstract/v12/DataType.h"
#include "Alembic/AbcCoreOgawa/v12/ReadArraySample.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t num_dimensions = stream.ConsumeIntegral<size_t>();
  std::vector<std::shared_ptr<Alembic::AbcCoreAbstract::v12::Dimension>>
      dimensions;
  dimensions.reserve(num_dimensions);
  for (size_t i = 0; i < num_dimensions; i++) {
    const size_t dimension_size = stream.ConsumeIntegral<size_t>();
    dimensions.push_back(std::make_shared<
        Alembic::AbcCoreAbstract::v12::Dimension>(dimension_size));
  }

  const size_t num_elements = stream.ConsumeIntegral<size_t>();
  const std::string data_type_name = stream.ConsumeRandomLengthString();
  Alembic::AbcCoreAbstract::v12::DataType data_type;
  if (data_type_name == "kBoolean") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kBooleanPOD, 1);
  } else if (data_type_name == "kCharacter") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kCharacterPOD, 1);
  } else if (data_type_name == "kFloat16") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kFloat16POD, 1);
  } else if (data_type_name == "kFloat32") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kFloat32POD, 1);
  } else if (data_type_name == "kFloat64") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kFloat64POD, 1);
  } else if (data_type_name == "kInt8") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kInt8POD, 1);
  } else if (data_type_name == "kInt16") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kInt16POD, 1);
  } else if (data_type_name == "kInt32") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kInt32POD, 1);
  } else if (data_type_name == "kInt64") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kInt64POD, 1);
  } else if (data_type_name == "kStringPOD") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kStringPOD, 1);
  } else if (data_type_name == "kWstringPOD") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kWstringPOD, 1);
  } else if (data_type_name == "kTimeSampling") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kTimeSampling, 1);
  } else if (data_type_name == "kUnknownPOD") {
    data_type = Alembic::AbcCoreAbstract::v12::DataType(
        Alembic::AbcCoreAbstract::v12::DataType::kUnknownPOD, 1);
  } else {
    return 0;
  }

  std::shared_ptr<std::vector<uint8_t>> data =
      std::make_shared<std::vector<uint8_t>>();
  data->resize(num_elements * data_type.getSize());

  std::shared_ptr<std::shared_ptr<void>> prop_ptr =
      std::make_shared<std::shared_ptr<void>>();

  Alembic::AbcCoreOgawa::v12::ReadArraySample(&dimensions, &data, num_elements,
                                               &data_type, &prop_ptr);
  return 0;
}