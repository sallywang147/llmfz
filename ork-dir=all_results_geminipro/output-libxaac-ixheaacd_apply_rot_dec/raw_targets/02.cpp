#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ia_ps_dec_struct ps_dec;
  int* a = new int[stream.ConsumeIntegral<size_t>()];
  int* b = new int[stream.ConsumeIntegral<size_t>()];
  int* c = new int[stream.ConsumeIntegral<size_t>()];
  int* d = new int[stream.ConsumeIntegral<size_t>()];
  struct ia_sbr_tables_struct sbr_tables;
  short* e = new short[stream.ConsumeIntegral<size_t>()];

  ixheaacd_apply_rot_dec(&ps_dec, a, b, c, d, &sbr_tables, e);

  delete[] a;
  delete[] b;
  delete[] c;
  delete[] d;
  delete[] e;
  return 0;
}