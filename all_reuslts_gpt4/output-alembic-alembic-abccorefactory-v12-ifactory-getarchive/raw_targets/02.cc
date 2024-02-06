#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Alembic/AbcCoreFactory/All.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Alembic::AbcCoreFactory::v12::IFactory factory;
  Alembic::Abc::v12::IArchive archive;
  std::vector<std::string> errors;
  int policy = stream.ConsumeIntegral<int>();

  factory.getArchive(&archive, &factory, &errors, &policy);

  return 0;
}