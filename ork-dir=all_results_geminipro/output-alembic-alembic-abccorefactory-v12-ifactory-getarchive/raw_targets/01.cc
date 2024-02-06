#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include <Alembic/Abc/v12/IArchive.h>
#include <Alembic/AbcCoreFactory/v12/IFactory.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<Alembic::Abc::v12::IArchive*> archives;
  std::vector<Alembic::AbcCoreFactory::v12::IFactory*> factories;
  std::vector<std::vector<uint8_t>> archives_data;
  std::vector<int> archive_sizes;
  while (stream.remaining_bytes() > 0) {
    archives_data.emplace_back(stream.ConsumeRemainingBytes());
    archive_sizes.emplace_back(archives_data.back().size());
  }
  for (size_t i = 0; i < archives_data.size(); ++i) {
    Alembic::Abc::v12::IArchive* archive =
        Alembic::Abc::v12::IArchive::create(
            archives_data[i].data(), archive_sizes[i],
            Alembic::Abc::v12::IArchive::kNoThrow);
    if (archive) archives.emplace_back(archive);
  }
  for (size_t i = 0; i < archives.size(); ++i) {
    Alembic::AbcCoreFactory::v12::IFactory* factory =
        Alembic::AbcCoreFactory::v12::IFactory::create();
    if (factory) factories.emplace_back(factory);
  }
  std::vector<std::vector<uint8_t>> data;
  std::vector<int> sizes;
  for (size_t i = 0; i < archives.size(); ++i) {
    data.emplace_back();
    sizes.emplace_back();
    archives[i]->getArchive(factories[i], &data.back(), &sizes.back());
  }
  for (size_t i = 0; i < archives.size(); ++i) {
    delete archives[i];
    delete factories[i];
  }
  return 0;
}