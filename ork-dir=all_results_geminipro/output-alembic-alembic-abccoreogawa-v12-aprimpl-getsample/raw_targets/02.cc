#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "Alembic/AbcCoreOgawa/v12/AprImpl.h"
#include "Alembic/AbcCoreOgawa/v12/OgawaIndex.h"
#include "Alembic/AbcCoreOgawa/v12/OgawaUtil.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Alembic::AbcCoreOgawa::v12::AprImpl apr;
  size_t index = stream.ConsumeIntegral<size_t>();
  std::shared_ptr<Alembic::AbcCoreOgawa::v12::OgawaIndex> ogawa_index =
      std::make_shared<Alembic::AbcCoreOgawa::v12::OgawaIndex>();
  std::shared_ptr<void> sample;
  apr.getSample(&(*ogawa_index), index, &sample);
  return 0;
}