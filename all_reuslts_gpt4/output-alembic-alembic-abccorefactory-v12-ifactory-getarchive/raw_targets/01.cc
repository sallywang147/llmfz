#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Alembic/AbcCoreFactory/v12/IFactory.h"
#include "Alembic/Abc/v12/IArchive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Alembic::AbcCoreFactory::v12::IFactory factory;
  Alembic::Abc::v12::IArchive archive;
  std::vector<std::string> strings;
  int numStrings = stream.ConsumeIntegral<int>();

  for (int i = 0; i < numStrings; ++i) {
    strings.push_back(stream.ConsumeRandomLengthString());
  }

  factory.getArchive(&archive, &factory, &strings, &numStrings);

  return 0;
}