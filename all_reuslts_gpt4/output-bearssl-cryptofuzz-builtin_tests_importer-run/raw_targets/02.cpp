#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cryptofuzz/Builtin_tests_importer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the union.anon object
  union.anon obj;

  // Consume data from the stream to fill the union.anon object
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // Create the Builtin_tests_importer object
  cryptofuzz::Builtin_tests_importer importer;

  // Run the function with the union.anon object
  importer.Run(&obj);

  return 0;
}