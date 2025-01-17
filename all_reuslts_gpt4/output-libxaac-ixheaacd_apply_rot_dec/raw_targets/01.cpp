#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "ixheaacd_type_def.h"
#include "ixheaacd_ps_dec.h"
#include "ixheaacd_sbr_rom.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ia_ps_dec_struct ps_dec_struct;
  struct ia_sbr_tables_struct sbr_tables_struct;

  // Initialize the structures with zero
  memset(&ps_dec_struct, 0, sizeof(ps_dec_struct));
  memset(&sbr_tables_struct, 0, sizeof(sbr_tables_struct));

  // Consume data for the parameters
  int param1 = stream.ConsumeIntegral<int>();
  int param2 = stream.ConsumeIntegral<int>();
  int param3 = stream.ConsumeIntegral<int>();
  int param4 = stream.ConsumeIntegral<int>();
  short param5 = stream.ConsumeIntegral<short>();

  // Call the function to fuzz
  ixheaacd_apply_rot_dec(&ps_dec_struct, &param1, &param2, &param3, &param4, &sbr_tables_struct, &param5);

  return 0;
}