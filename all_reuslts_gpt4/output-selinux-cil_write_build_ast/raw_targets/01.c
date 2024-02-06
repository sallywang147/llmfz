#include <stdio.h>
#include <sepol/cil/cil.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    struct cil_db *db = NULL;
    struct _IO_FILE *out = NULL;

    // Initialize the CIL database
    cil_db_init(&db);

    // Parse the data into the CIL database
    cil_add_file(db, "fuzz", (char *)data, size);
    cil_compile(db);
    cil_build_policydb(db);

    // Open a file for writing
    out = fopen("/dev/null", "w");
    if (out == NULL) {
        cil_db_destroy(&db);
        return 0;
    }

    // Call the function to fuzz
    cil_write_build_ast(out, db);

    // Clean up
    fclose(out);
    cil_db_destroy(&db);

    return 0;
}