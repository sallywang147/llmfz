#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cil.h"

extern "C" {
#include "cil_db.h"
#include "cil_write_build_ast.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    cil_init();
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> output_buffer(provider.ConsumeIntegralInRange<size_t>(
      0, 1024 * 1024));
  FILE* output_file = fmemopen(output_buffer.data(), output_buffer.size(), "w");

  cil_db* db = cil_db_new();
  cil_db_add_file(db, provider.ConsumeBytesAsString(provider.ConsumeIntegralInRange<size_t>(
      0, 1024 * 1024)).c_str(), CIL_DB_FILE_SOURCE);

  cil_write_build_ast(output_file, db);

  cil_db_free(db);
  fclose(output_file);

  return 0;
}
```

The original code had no issues, so no changes were made.