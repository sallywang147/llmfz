#include <coap3/coap.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  coap_context_t *ctx = coap_new_context(NULL);
  if (!ctx) {
    return 0;
  }
  FuzzedDataProvider provider(data, size);
  const size_t path_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  const size_t db_path_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  const size_t log_path_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  const int enable = provider.ConsumeBool();
  char *path = provider.ConsumeBytes<char>(path_size).data();
  char *db_path = provider.ConsumeBytes<char>(db_path_size).data();
  char *log_path = provider.ConsumeBytes<char>(log_path_size).data();

  // Enable debug logging
  coap_set_log_level(LOG_DEBUG);

  // Initialize the persistence layer
  coap_persist_startup(ctx, path, db_path, log_path, enable);

  // Free the context
  coap_free_context(ctx);

  return 0;
}