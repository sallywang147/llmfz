#include <sepol/policydb/policydb.h>
#include <sepol/handle.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the sepol handle
  struct sepol_handle *handle = sepol_handle_create();
  if (!handle) {
    return 0;
  }

  // Initialize the policydb
  struct sepol_policydb *p = (struct sepol_policydb *)malloc(sizeof(struct sepol_policydb));
  if (!p) {
    sepol_handle_destroy(handle);
    return 0;
  }
  sepol_policydb_init(p);

  // Initialize newdata and newlen
  char *newdata = NULL;
  size_t newlen = 0;

  // Call the target function
  int result = sepol_policydb_to_image(handle, p, &newdata, &newlen);

  // Clean up
  sepol_policydb_destroy(p);
  free(p);
  sepol_handle_destroy(handle);
  if (newdata) {
    free(newdata);
  }

  return 0;
}