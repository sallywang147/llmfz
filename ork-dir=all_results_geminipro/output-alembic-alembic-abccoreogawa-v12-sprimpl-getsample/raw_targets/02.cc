#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "AbcCoreOgawa/SprImpl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  Alembic::AbcCoreOgawa::v12::SprImpl spr_impl;
  const size_t sample_index = stream.ConsumeIntegral<size_t>();
  std::vector<char> sample_buffer(stream.ConsumeIntegralInRange(1, 100000));
  spr_impl.getSample(&spr_impl, sample_index, sample_buffer.data());
  return 0;
}