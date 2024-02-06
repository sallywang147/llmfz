#include <sepol/policydb/policydb.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);
    
    struct sepol_handle *handle = sepol_handle_create();
    if (!handle) {
        return 0;
    }

    struct policydb policydb;
    if (policydb_init(&policydb)) {
        sepol_handle_destroy(handle);
        return 0;
    }

    char *newdata;
    size_t newlen;

    policydb_to_image(handle, &policydb, &newdata, &newlen);

    sepol_handle_destroy(handle);
    policydb_destroy(&policydb);
    free(newdata);

    return 0;
}