#include "Alembic/AbcCoreOgawa/v12/AprImpl.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  size_t sample_index = provider.ConsumeIntegral<size_t>();
  std::shared_ptr<Alembic::Abc::OObject> sample;
  Alembic::AbcCoreOgawa::v12::AprImpl::getSample(nullptr, sample_index, &sample);
  return 0;
}