#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "absl/strings/str_format.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* spec = stream.ConsumeRandomLengthString().c_str();
  const long long arg = stream.ConsumeIntegral<long long>();

  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal::FormatArgImpl::Dispatch<long long>(
      const_cast<char*>(spec), strlen(spec), 0, nullptr);
  absl::str_format_internal