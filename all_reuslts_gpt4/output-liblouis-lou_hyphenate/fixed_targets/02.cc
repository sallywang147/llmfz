#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <liblouis.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // We need at least 1 byte for mode and 1 byte for inlen.
  if (size < 2) {
    return 0;
  }

  // Extract mode as a byte.
  int mode = stream.ConsumeIntegral<uint8_t>();

  // Extract inlen as a byte.
  int inlen = stream.ConsumeIntegral<uint8_t>();

  // We need at least inlen bytes for inbuf and inlen bytes for hyphens.
  if (stream.remaining_bytes() < 2 * inlen) {
    return 0;
  }

  // Extract inbuf as a short array.
  std::vector<short> inbuf = stream.ConsumeBytes<short>(inlen);
  
  // Extract hyphens as a char array.
  std::vector<char> hyphens = stream.ConsumeBytes<char>(inlen);

  // Use the remaining bytes for tableList.
  std::string tableList = stream.ConsumeRemainingBytesAsString();

  // Call the function to fuzz.
  lou_hyphenate(const_cast<char*>(tableList.c_str()), inbuf.data(), inlen, hyphens.data(), mode);

  return 0;
}