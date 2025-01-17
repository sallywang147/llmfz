#include <sepol/cil/cil.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file for writing
  FILE* temp_file = tmpfile();
  if (temp_file == NULL) {
    return 0;
  }

  // Initialize the CIL database
  struct cil_db *db = NULL;
  cil_db_init(&db);

  // Consume the remaining bytes to create a string
  std::string cil_code = stream.ConsumeRemainingBytesAsString();

  // Parse the CIL code
  if (cil_add_file(db, "fuzz", cil_code.c_str(), cil_code.size()) == SEPOL_OK) {
    if (cil_compile(db) == SEPOL_OK) {
      if (cil_build_policydb(db) == SEPOL_OK) {
        // Call the function to fuzz
        cil_write_resolve_ast(temp_file, db);
      }
    }
  }

  // Clean up
  cil_db_destroy(&db);
  fclose(temp_file);

  return 0;
}