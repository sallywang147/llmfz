#include <fuzzer/FuzzedDataProvider.h>
#include <absl/strings/str_format.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume values for the parameters
  char arg = stream.ConsumeIntegral<char>();
  size_t spec = stream.ConsumeIntegral<size_t>();
  int out = stream.ConsumeIntegral<int>();

  // Consume a random length string
  std::string str = stream.ConsumeRandomLengthString();
  char* ptr = const_cast<char*>(str.c_str());

  // Create an instance of FormatArgImpl
  absl::str_format_internal::FormatArgImpl formatArgImpl;

  // Call the target function
  formatArgImpl.Dispatch<char>(&arg, spec, out, ptr);

  return 0;
}