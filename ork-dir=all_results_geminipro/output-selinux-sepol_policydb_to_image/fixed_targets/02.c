#include <sepol/policydb/policydb.h>

extern "C" {
#include <sepol/policydb/policydb.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  sepol_handle_t *handle = sepol_handle_create();
  if (!handle) {
    return 1;
  }
  sepol_policydb_t *policydb = sepol_policydb_create();
  if (!policydb) {
    sepol_handle_destroy(handle);
    return 1;
  }
  char *newdata = nullptr;
  size_t newlen = 0;

  int rc = sepol_policydb_read(handle, policydb, data, size);
  if (rc != 0) {
    sepol_policydb_free(policydb);
    sepol_handle_destroy(handle);
    return 1;
  }
  rc = sepol_policydb_to_image(handle, policydb, &newdata, &newlen);
  if (rc != 0) {
    sepol_policydb_free(policydb);
    sepol_handle_destroy(handle);
    return 1;
  }

  sepol_policydb_free(policydb);
  sepol_handle_destroy(handle);
  free(newdata);

  return 0;
}