#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ixheaacd_type_def.h"
#include "ixheaacd_ps_dec.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create and initialize the parameters for ixheaacd_apply_rot_dec function.
  struct ia_ps_dec_struct ps_dec_struct;
  int int_array1[4];
  int int_array2[4];
  int int_array3[4];
  int int_array4[4];
  struct ia_sbr_tables_struct sbr_tables_struct;
  short short_array[4];

  // Use FuzzedDataProvider to fill the parameters with data.
  size_t consumed = stream.ConsumeData(&ps_dec_struct, sizeof(ps_dec_struct));
  if(consumed != sizeof(ps_dec_struct)) return 0;
  
  for(int i = 0; i < 4; i++) {
    int_array1[i] = stream.ConsumeIntegral<int>();
    int_array2[i] = stream.ConsumeIntegral<int>();
    int_array3[i] = stream.ConsumeIntegral<int>();
    int_array4[i] = stream.ConsumeIntegral<int>();
    short_array[i] = stream.ConsumeIntegral<short>();
  }

  consumed = stream.ConsumeData(&sbr_tables_struct, sizeof(sbr_tables_struct));
  if(consumed != sizeof(sbr_tables_struct)) return 0;

  // Call the function with the fuzzed parameters.
  ixheaacd_apply_rot_dec(&ps_dec_struct, int_array1, int_array2, int_array3, int_array4, &sbr_tables_struct, short_array);

  return 0;
}