#include <Alembic/AbcCoreFactory/v1/IFactory.h>
#include <Alembic/AbcCoreOgawa/v1/Ogawa.h>
#include <Alembic/AbcGeom/v1/All.h>
#include <Alembic/AbcMaterial/v1/All.h>

extern "C" {
#include <Alembic/AbcCoreFactory/v12/IFactory.h>
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  Alembic::Abc::v12::IArchive archive;
  Alembic::AbcCoreFactory::v12::IFactory factory;
  std::vector<Alembic::AbcCoreFactory::v12::IFactory::CoreType> types;
  factory.getArchive(&archive, &factory, &types);
}