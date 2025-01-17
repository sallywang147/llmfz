#include <stdlib.h>
#include <time.h>

#include <ck_hash.h>

#include "fuzz_format.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ck_hash_table_t *table = ck_hash_init(CK_HASH_MODE_DEFAULT, ck_float_hash, ck_float_compare, ck_null_hash, NULL);
  if (table == NULL) {
    return 0;
  }

  FuzzedDataProvider provider(Data, Size);
  while (provider.remaining_bytes() > 0) {
    float key = provider.ConsumeFloatingPoint<float>();
    size_t value_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
    char *value = (char *)malloc(value_size + 1);
    if (value == NULL) {
      return 0;
    }
    provider.ConsumeBytes(value, value_size);
    value[value_size] = '\0';
    ck_float_hash_insert(key, value, table);
    free(value);
  }

  ck_hash_destroy(table);

  return 0;
}