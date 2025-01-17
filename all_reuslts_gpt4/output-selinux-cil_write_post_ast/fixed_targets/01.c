#include <fuzzer/FuzzedDataProvider.h>
#include <sepol/cil/cil.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize CIL database
  struct cil_db *db;
  cil_db_init(&db);
  cil_set_disable_neverallow(db, CIL_TRUE);
  cil_set_multiple_decls(db, CIL_TRUE);
  cil_set_disable_dontaudit(db, CIL_TRUE);
  cil_set_disable_permissive(db, CIL_TRUE);
  cil_set_disable_policycap(db, CIL_TRUE);
  cil_set_disable_avrule(db, CIL_TRUE);
  cil_set_disable_typebounds(db, CIL_TRUE);
  cil_set_disable_nametypetransition(db, CIL_TRUE);
  cil_set_disable_rangetransition(db, CIL_TRUE);
  cil_set_disable_roletransition(db, CIL_TRUE);

  // Parse the input data
  char *input_data = stream.ConsumeRemainingBytesAsString().c_str();
  if (cil_add_file(db, "fuzz", input_data, CIL_FALSE)) {
    cil_db_destroy(&db);
    return 0;
  }

  if (cil_compile(db)) {
    cil_db_destroy(&db);
    return 0;
  }

  if (cil_build_policydb(db)) {
    cil_db_destroy(&db);
    return 0;
  }

  // Write the post-AST to a file
  FILE *out = tmpfile();
  if (out == NULL) {
    cil_db_destroy(&db);
    return 0;
  }

  cil_write_post_ast(out, db);

  // Cleanup
  fclose(out);
  cil_db_destroy(&db);

  return 0;
}