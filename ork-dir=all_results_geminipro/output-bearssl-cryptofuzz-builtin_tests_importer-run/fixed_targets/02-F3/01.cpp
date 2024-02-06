#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "cryptofuzz.h"

extern "C" {
#include "union.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  union.anon* anon_struct = new union.anon;
  memset(anon_struct, 0, sizeof(union.anon));
  anon_struct->type = stream.ConsumeIntegralInRange<uint8_t>(0, 10);
  cryptofuzz::Builtin_tests_importer::Run(anon_struct);
  delete anon_struct;
  return 0;
}