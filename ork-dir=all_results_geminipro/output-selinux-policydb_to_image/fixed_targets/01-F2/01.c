#include <sepol/policydb/policydb.h>
#include <sepol/policydb/policydb_write.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  sepol_handle_t *handle = sepol_handle_create();
  if (!handle) {
    return 0;
  }
  policydb_t *policydb = policydb_create();
  if (!policydb) {
    sepol_handle_destroy(handle);
    return 0;
  }

  FuzzedDataProvider provider(data, size);
  size_t policydb_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  auto policydb_data = provider.ConsumeBytes<char>(policydb_size);
  if (policydb_read(policydb, policydb_data.data(), policydb_data.size())) {
    policydb_destroy(policydb);
    sepol_handle_destroy(handle);
    return 0;
  }

  char *newdata = nullptr;
  size_t newlen = 0;
  if (policydb_write(handle, policydb, &newdata, &newlen)) {
    policydb_destroy(policydb);
    sepol_handle_destroy(handle);
    return 0;
  }
  free(newdata);

  policydb_destroy(policydb);
  sepol_handle_destroy(handle);
  return 0;
}