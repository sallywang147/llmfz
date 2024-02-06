#include <fuzzing/datasource/datasource.hpp>
#include <fuzzing/types/container.hpp>
#include <cstddef>
#include <cstdint>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  fuzzing::datasource::Datasource ds(data, size);
  const auto numElements = ds.Get<uint64_t>() % 1024;
  fuzzing::types::Container<char, true, false> c(numElements);
  c.~Container();
  return 0;
}