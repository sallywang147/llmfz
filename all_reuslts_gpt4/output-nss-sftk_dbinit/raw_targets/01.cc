#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char *arg1 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *arg2 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *arg3 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *arg4 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *arg5 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *arg6 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  char *arg7 = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  int arg8 = stream.ConsumeIntegral<int>();
  int arg9 = stream.ConsumeIntegral<int>();
  int arg10 = stream.ConsumeIntegral<int>();
  int arg11 = stream.ConsumeIntegral<int>();
  int arg12 = stream.ConsumeIntegral<int>();
  SFTKDBHandleStr *arg13 = nullptr;
  SFTKDBHandleStr *arg14 = nullptr;

  size_t result = sftk_DBInit(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, &arg13, &arg14);

  return 0;
}