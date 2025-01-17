#include <utf8proc.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2)
    return 0;

  // Avoid timeout with long inputs
  if (size > (64 * 1024))
    return 0;

  FuzzedDataProvider stream(data, size);

  size_t str_size = stream.ConsumeIntegralInRange<size_t>(1, size - 1);
  std::string str = stream.ConsumeBytesAsString(str_size);
  char *utf8_str = const_cast<char *>(str.c_str());

  size_t buffer_size = size - str_size;
  int *buffer = new int[buffer_size];

  utf8proc_option_t options = stream.ConsumeIntegral<utf8proc_option_t>();

  utf8proc_decompose(utf8_str, str_size, buffer, buffer_size, options);

  delete[] buffer;

  return 0;
}