#include <fuzzer/FuzzedDataProvider.h>
#include <woff2/decode.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t length = stream.remaining_bytes() / 2;
  std::string result(length, 0);
  std::string input = stream.ConsumeBytesAsString(length);

  woff2::ConvertWOFF2ToTTF(result.data(), result.size(), input.data(), input.size());

  return 0;
}