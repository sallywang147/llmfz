#include <fuzzer/FuzzedDataProvider.h>
#include <sepol/cil/cil.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize CIL database
  struct cil_db *db;
  cil_db_init(&db);

  // Parse the data into the CIL database
  cil_add_file(db, "fuzzed.cil", (char *)data, size);
  cil_compile(db);
  cil_build_policydb(db);

  // Write the resolved AST to a file
  FILE *out = tmpfile();
  if (out == NULL) {
    cil_db_destroy(&db);
    return 0;
  }

  cil_write_resolve_ast(out, db);

  // Cleanup
  fclose(out);
  cil_db_destroy(&db);

  return 0;
}