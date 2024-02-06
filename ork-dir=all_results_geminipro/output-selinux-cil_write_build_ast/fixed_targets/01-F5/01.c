#include "fuzzer/FuzzedDataProvider.h"

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cil.h"

extern "C" {
#include "cil_internal.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct cil_db db;
  cil_db_init(&db);

  // Initialize the database.
  int ret = cil_db_load_module(&db, provider.ConsumeRandomLengthString().c_str());
  if (ret != 0) {
    cil_db_destroy(&db);
    return 0;
  }

  // Create a temporary file.
  FILE* tmpfile = tmpfile();
  if (tmpfile == nullptr) {
    cil_db_destroy(&db);
    return 0;
  }

  // Write the AST to the temporary file.
  ret = cil_write_build_ast(tmpfile, &db);
  if (ret != 0) {
    fclose(tmpfile);
    cil_db_destroy(&db);
    return 0;
  }

  // Close the temporary file.
  fclose(tmpfile);

  // Destroy the database.
  cil_db_destroy(&db);

  return 0;
}