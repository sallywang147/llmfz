#include <sepol/policydb.h>
#include <sepol/handle.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  sepol_handle_t *handle = sepol_handle_create();
  if (!handle) {
    return 0;
  }

  sepol_policydb_t *policydb = sepol_policydb_create();
  if (!policydb) {
    sepol_handle_destroy(handle);
    return 0;
  }

  char *newdata = nullptr;
  size_t newlen = 0;

  sepol_policydb_to_image(handle, policydb, &newdata, &newlen);

  sepol_policydb_free(policydb);
  sepol_handle_destroy(handle);
  free(newdata);

  return 0;
}