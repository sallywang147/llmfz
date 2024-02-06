#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "Alembic/AbcCoreOgawa/v12/SprImpl.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t sample_index = stream.ConsumeIntegral<size_t>();
  std::vector<char> sample_buffer(stream.ConsumeIntegralInRange<size_t>(
      0, std::numeric_limits<size_t>::max()));
  char* sample_buffer_ptr = sample_buffer.data();
  Alembic::AbcCoreOgawa::v12::SprImpl::getSample(nullptr, sample_index,
                                                sample_buffer_ptr);
  return 0;
}