#include <fuzzer/FuzzedDataProvider.h>
#include <woff2/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t result_length = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::string result(result_length, 0);
  auto remaining_data = provider.ConsumeRemainingBytes<char>();
  woff2::ConvertWOFF2ToTTF(result.data(), result_length, remaining_data.data(), remaining_data.size());
  return 0;
}