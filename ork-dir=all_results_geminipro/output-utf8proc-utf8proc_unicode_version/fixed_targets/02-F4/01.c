#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <utf8proc.h>

extern "C" {
#include <unicode/utf8.h>
}

// Fuzzing entry point.
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize utf8proc library.
  utf8proc_ssize_t version_length = utf8proc_unicode_version();
  (void)version_length;  // Avoid unused variable warning.

  // Create a FuzzedDataProvider object to parse the input data.
  FuzzedDataProvider data_provider(data, size);

  // Read a sequence of UTF-8 characters from the input data.
  std::string utf8_string = data_provider.ConsumeRandomLengthString(size);

  // Convert the UTF-8 string to a sequence of Unicode code points.
  int32_t *code_points = nullptr;
  int32_t code_point_count = 0;
  utf8proc_int32seq_size_t seq_size = utf8proc_decompose(
      (const utf8proc_uint8_t *)utf8_string.c_str(), utf8_string.length(),
      &code_points, &code_point_count);

  // Check if the conversion was successful.
  if (seq_size == UTF8PROC_ERROR_INVALID_UTF8) {
    return 0;
  }

  // Process the sequence of Unicode code points.
  for (int i = 0; i < code_point_count; i++) {
    // Do something with the code point. For example, print it to the console.
    printf("%c", code_points[i]);
  }

  // Free the memory allocated for the sequence of Unicode code points.
  free(code_points);

  return 0;
}