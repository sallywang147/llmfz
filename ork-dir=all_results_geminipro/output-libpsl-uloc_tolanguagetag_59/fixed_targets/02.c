#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <unicode/uloc.h>

extern "C" {
#include <unicode/uloc.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<uint8_t> locale_id_bytes(data, data + size);
  locale_id_bytes.push_back('\0');
  const char* locale_id = reinterpret_cast<const char*>(locale_id_bytes.data());

  std::vector<uint8_t> langtag_bytes(size, 0);
  langtag_bytes.push_back('\0');
  char* langtag = reinterpret_cast<char*>(langtag_bytes.data());

  int langtag_capacity = size;
  int status = 0;

  uloc_toLanguageTag(locale_id, langtag, langtag_capacity, &status);

  return 0;
}