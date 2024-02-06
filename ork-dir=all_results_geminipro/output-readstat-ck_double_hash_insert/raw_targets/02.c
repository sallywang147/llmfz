#include <stdlib.h>
#include <time.h>

#include <ck_pr.h>
#include <ck_hash.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ck_hash_t hash;
  ck_hash_init(&hash, CK_MD5_HASH);

  struct ck_hash_table_s *table = ck_hash_new(&hash, CK_MD5_HASH, 1024);
  if (table == NULL) {
    return 0;
  }

  FuzzedDataProvider stream(Data, Size);

  while (stream.remaining_bytes() > 0) {
    double key = stream.ConsumeFloatingPoint<double>();
    std::string value = stream.ConsumeRemainingBytesAsString();

    ck_double_hash_insert(key, value.c_str(), table);
  }

  ck_hash_destroy(table);

  return 0;
}