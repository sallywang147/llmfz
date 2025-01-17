#include <sepol/policydb/policydb.h>
#include <fuzzer/FuzzedDataProvider.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct sepol_handle *handle = sepol_handle_create();
    struct policydb policydb;
    char *newdata = NULL;
    size_t newlen = 0;

    policydb_init(&policydb);

    // Consume the data as a string
    std::string policyData = stream.ConsumeRemainingBytesAsString();
    policydb_read(&policydb, policyData.c_str(), policyData.size());

    // Call the target function
    policydb_to_image(handle, &policydb, &newdata, &newlen);

    // Cleanup
    sepol_handle_destroy(handle);
    policydb_destroy(&policydb);
    free(newdata);

    return 0;
}