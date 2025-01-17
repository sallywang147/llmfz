#include <fuzzer/FuzzedDataProvider.h>
#include <sepol/cil/cil.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct cil_db *db = NULL;
  FILE *out = tmpfile();

  if (cil_db_init(&db) != SEPOL_OK) {
    goto exit;
  }

  if (cil_add_file(db, "fuzzed", (char *)stream.ConsumeRemainingBytes().data(), size) != SEPOL_OK) {
    goto exit;
  }

  if (cil_compile(db) != SEPOL_OK) {
    goto exit;
  }

  if (cil_build_policydb(db) != SEPOL_OK) {
    goto exit;
  }

  if (cil_write_post_ast(out, db) != SEPOL_OK) {
    goto exit;
  }

exit:
  if (db != NULL) {
    cil_db_destroy(&db);
  }

  if (out != NULL) {
    fclose(out);
  }

  return 0;
}