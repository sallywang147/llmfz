#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "cryptofuzz.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t anon_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  std::vector<uint8_t> anon_bytes;
  anon_bytes.resize(anon_size);
  stream.ConsumeBytes<uint8_t>(&anon_bytes[0], anon_size);

  union.anon anon;
  std::memcpy(&anon, anon_bytes.data(), anon_size);

  cryptofuzz::Builtin_tests_importer importer;
  importer.Run(&anon);
  return 0;
}