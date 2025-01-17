#include <fuzzer/FuzzedDataProvider.h>
#include <absl/strings/str_format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  long long arg = stream.ConsumeIntegral<long long>();
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();

  // Extract a string
  std::string str = stream.ConsumeRandomLengthString();
  char *ptr = const_cast<char*>(str.c_str());

  // Create FormatArgImpl object
  absl::str_format_internal::FormatArgImpl argImpl;

  // Call the function
  bool result = argImpl.Dispatch<long long>(arg, spec, out, ptr);

  return 0;
}