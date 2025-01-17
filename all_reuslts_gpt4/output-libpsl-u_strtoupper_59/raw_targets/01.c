#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <unicode/utypes.h>
#include <unicode/ustring.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int destCapacity = 256;
  UChar dest[destCapacity];
  int32_t pErrorCode = 0;

  std::vector<uint8_t> src_bytes = stream.ConsumeBytes<uint8_t>(stream.remaining_bytes() / 2);
  UChar* src = reinterpret_cast<UChar*>(src_bytes.data());
  int32_t srcLength = src_bytes.size() / sizeof(UChar);

  std::string locale = stream.ConsumeRemainingBytesAsString();

  u_strToUpper_59(dest, destCapacity, src, srcLength, locale.c_str(), &pErrorCode);

  return 0;
}