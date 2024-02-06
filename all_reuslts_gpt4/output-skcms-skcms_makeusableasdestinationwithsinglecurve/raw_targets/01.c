#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <skcms.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  skcms_ICCProfile profile;

  // Try to parse the data as an ICC profile
  if (!skcms_Parse(stream.ConsumeRemainingBytes().data(), size, &profile)) {
    return 0;
  }

  // Call the function under test
  skcms_MakeUsableAsDestinationWithSingleCurve(&profile);

  return 0;
}