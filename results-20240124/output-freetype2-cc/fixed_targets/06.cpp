 #include <fuzzer/FuzzedDataProvider.h>

#include <stdint.h>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg = stream.ConsumeIntegral<int>();
  int int_arg_in_range = stream.ConsumeIntegralInRange(-100, 100);
  bool bool_arg = stream.ConsumeBool();

  // Extract floating point values
  float probability = stream.ConsumeProbability();
  double double_arg = stream.ConsumeFloatingPoint<double>();
  double double_arg_in_range = stream.ConsumeFloatingPointInRange(-1.0, 1.0);

  // Extract value from predefined set, such as enum or array
  EnumType enum = stream.ConsumeEnum<EnumType>();
  int valid_values = stream.PickValueInArray({FLAG_1, FLAG_2, FLAG_3});

  // Extract an array of bytes as a vector. You MUST call .data() to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, max_size));
  void *data_ptr = bytes.data();
  std::vector<uint8_t> bytes2 = stream.ConsumeBytes<uint8_t>(requested_size);
  void *data2_ptr = bytes2.data();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, max_size));
  char *ptr = str.c_str();
  std::string str2 = stream.ConsumeBytesAsString(requested_size);
  char *ptr2 = str2.c_str();
  std::string str3 = stream.ConsumeRandomLengthString();
  char *ptr3 = str3.c_str();

  // Extract to user defined object
  struct_type_t obj;
  size_t consumed = stream.ConsumeData(&obj, sizeof(obj));

  // There MUST be AT MOST ONE call to ConsumeRemainingBytes to consume remaining input!
  std::vector<uint8_t> bytes3 = stream.ConsumeRemainingBytes();
  void *data3_ptr = bytes3.data();

  // All variables used MUST be declared and initialized. Carefully make sure that the variable and argument types in your code match and compiles successfully. Add type casts to make types match.

  // Do not create new variables with the same names as existing variables.
  // WRONG:
  // int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  //   void* data = Foo();
  // }

  // EXTREMELY IMPORTANT: If you write code using goto, you MUST MUST also declare all variables BEFORE the goto. Never introduce new variables after the goto.
  // WRONG:
  // int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  //   int a = bar();
  //   if (!some_function()) goto EXIT;
  //   Foo b = target_function(data, size);
  //   int c = another_func();
  // EXIT:
  //   return 0;
  // }

  // CORRECT:
  // int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  //   int a = bar();
  //   Foo b;
  //   int c;

  //   if (!some_function()) goto EXIT;
  //   b = target_function(data, size);
  //   c = another_func()
  // EXIT:
  //   return 0;
  // }

  // If an example provided for the same library includes a unique header file, then it must be included in the solution as well.

  void _GLOBAL__sub_I_ftfuzzer.cc();

  return 0;
}