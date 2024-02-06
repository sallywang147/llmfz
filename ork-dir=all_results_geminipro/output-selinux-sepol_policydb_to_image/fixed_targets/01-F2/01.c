#include <sepol/policydb/policydb.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  sepol_handle_t *handle = sepol_handle_create();
  sepol_policydb_t *policydb = sepol_policydb_create();

  FuzzedDataProvider provider(data, size);
  const size_t policydb_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  const auto policydb_bytes = provider.ConsumeBytes<uint8_t>(policydb_size);
  sepol_policydb_read(handle, policydb, policydb_bytes.data(), policydb_bytes.size());

  char *newdata = nullptr;
  size_t newlen = 0;
  sepol_policydb_to_image(handle, policydb, &newdata, &newlen);

  free(newdata);

  sepol_policydb_free(policydb);
  sepol_handle_destroy(handle);

  return 0;
}