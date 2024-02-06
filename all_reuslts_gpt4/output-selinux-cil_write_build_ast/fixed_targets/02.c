#include <fuzzer/FuzzedDataProvider.h>
#include <sepol/cil/cil.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Initialize the CIL database
    struct cil_db *db = NULL;
    cil_db_init(&db);

    // Initialize the file
    FILE *out = tmpfile();
    if (out == NULL) {
        cil_db_destroy(&db);
        return 0;
    }

    // Call the function to be fuzzed
    cil_write_build_ast(out, db);

    // Clean up
    fclose(out);
    cil_db_destroy(&db);

    return 0;
}