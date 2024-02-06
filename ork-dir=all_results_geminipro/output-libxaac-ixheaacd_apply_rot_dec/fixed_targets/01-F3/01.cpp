#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "ia_ps_dec.h"
#include "ia_sbr_tables.h"

#include "ixheaacd_apply_rot_dec.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ia_ps_dec_struct ps_dec_struct;
  int *rot_dec_idx = new int;
  int *rot_dec_idx_prev = new int;
  int *rot_dec_idx_next = new int;
  int *rot_dec_idx_next_prev = new int;
  ia_sbr_tables_struct sbr_tables_struct;
  short *rot_dec_coeffs = new short[1024];
  ixheaacd_apply_rot_dec(&ps_dec_struct, rot_dec_idx, rot_dec_idx_prev,
                         rot_dec_idx_next, rot_dec_idx_next_prev,
                         &sbr_tables_struct, rot_dec_coeffs);
  delete[] rot_dec_idx;
  delete[] rot_dec_idx_prev;
  delete[] rot_dec_idx_next;
  delete[] rot_dec_idx_next_prev;
  delete[] rot_dec_coeffs;
  return 0;
}
```

The missing header file `ixheaacd_apply_rot_dec.h` is included.