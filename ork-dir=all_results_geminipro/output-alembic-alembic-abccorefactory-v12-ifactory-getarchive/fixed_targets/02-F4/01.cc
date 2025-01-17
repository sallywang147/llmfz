#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "Alembic/AbcCoreFactory/v12/IFactory.h"
#include "Alembic/Abc/v12/IArchive.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  std::string filename(reinterpret_cast<char*>(bytes.data()), bytes.size());
  Alembic::AbcCoreFactory::v12::IFactory factory;
  Alembic::Abc::v12::IArchive archive;
  std::vector<Alembic::AbcCoreFactory::v12::IFactory*> factories;
  int num_factories = 0;
  if (factory.getArchive(filename.c_str(), &archive, &factory, &factories, &num_factories) != 0) {
    return 0;
  }
  return 0;
}