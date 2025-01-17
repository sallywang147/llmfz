#include <fuzzer/FuzzedDataProvider.h>
#include <tsm.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  struct tsm_symbol_table *tbl = tsm_symbol_table_new();
  if (tbl == nullptr) {
    return 0;
  }

  int sym = fuzzed_data.ConsumeIntegral<int>();
  int ucs4 = fuzzed_data.ConsumeIntegral<int>();

  tsm_symbol_append(tbl, sym, ucs4);

  tsm_symbol_table_unref(tbl);

  return 0;
}