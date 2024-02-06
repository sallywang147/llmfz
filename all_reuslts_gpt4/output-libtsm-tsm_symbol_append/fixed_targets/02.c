#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "libtsm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct tsm_symbol_table *tbl;
  if (tsm_symbol_table_new(&tbl) < 0) {
    return 0;
  }

  int sym = stream.ConsumeIntegral<int>();
  int ucs4 = stream.ConsumeIntegral<int>();

  tsm_symbol_append(tbl, sym, ucs4);

  tsm_symbol_table_unref(tbl);

  return 0;
}