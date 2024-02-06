#include <sepol/policydb/policydb.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  sepol_handle_t *handle = sepol_handle_create();
  policydb_t policydb;
  char *newdata = nullptr;
  size_t newlen = 0;

  if (policydb_init(&policydb)) {
    goto exit;
  }

  if (policydb_read(&policydb, data, size)) {
    goto exit;
  }

  if (policydb_to_image(handle, &policydb, &newdata, &newlen)) {
    goto exit;
  }

exit:
  sepol_handle_destroy(handle);
  policydb_destroy(&policydb);
  free(newdata);
  return 0;
}