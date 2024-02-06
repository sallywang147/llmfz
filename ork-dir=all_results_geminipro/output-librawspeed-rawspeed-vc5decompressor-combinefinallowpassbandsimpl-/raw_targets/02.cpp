#include "rawspeed/VC5Decompressor.h"
#include <cassert>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider stream(Data, Size);

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, Size));
  void *data_ptr = bytes.data();

  // Extract integral values
  int int_arg = stream.ConsumeIntegral<int>();
  int int_arg_in_range = stream.ConsumeIntegralInRange(-100, 100);
  bool bool_arg = stream.ConsumeBool();

  // Extract floating point values
  float probability = stream.ConsumeProbability();
  double double_arg = stream.ConsumeFloatingPoint<double>();
  double double_arg_in_range = stream.ConsumeFloatingPointInRange(-1.0, 1.0);

  // Extract value from predefined set, such as enum or array
  // EnumType enum = stream.ConsumeEnum<EnumType>();
  // int valid_values = stream.PickValueInArray({FLAG_1, FLAG_2, FLAG_3});

  // Extract to user defined object
  // struct_type_t obj;
  // size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  rawspeed::VC5Decompressor::combineFinalLowpassBandsImpl<(rawspeed::VC5Decompressor *)const>(
      data_ptr, int_arg, int_arg_in_range, bool_arg, probability, double_arg, double_arg_in_range);

  return 0;
}