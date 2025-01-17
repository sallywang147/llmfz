#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cryptofuzz/Builtin_tests_importer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  cryptofuzz::Builtin_tests_importer importer;

  // Define a union.anon object
  union.anon obj;

  // Consume data to populate the union.anon object
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // Run the function with the populated object
  importer.Run(&obj);

  return 0;
}