#include "libtsm.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct tsm_symbol_table *tbl = tsm_symbol_table_new();
  FuzzedDataProvider stream(data, size);

  int sym = stream.ConsumeIntegral<int>();
  int ucs4 = stream.ConsumeIntegral<int>();

  int ret = tsm_symbol_append(tbl, sym, ucs4);
  tsm_symbol_table_unref(tbl);
  return ret;
}