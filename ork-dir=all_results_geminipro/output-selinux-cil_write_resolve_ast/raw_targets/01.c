#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cil/cil.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  cil_db db;
  cil_db_init(&db);

  cil_db_add_policy(&db, provider.ConsumeRandomLengthString().c_str());

  FILE* out = fopen("/dev/null", "w");
  if (out == nullptr) {
    return 0;
  }

  cil_write_resolve_ast(out, &db);

  fclose(out);
  cil_db_destroy(&db);
  return 0;
}