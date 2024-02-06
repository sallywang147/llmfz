#include <fuzzer/FuzzedDataProvider.h>
#include <re.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  struct re_guts* guts;
  FuzzedDataProvider provider(data, size);

  // Generate a random regex string.
  size_t regex_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> regex_bytes =
      provider.ConsumeBytes<uint8_t>(regex_size);
  char* regex = reinterpret_cast<char*>(regex_bytes.data());

  // Compile the regex.
  if (re_compile(&guts, regex, 0, 0) != 0) {
    return 0;
  }

  // Generate a random input string.
  size_t input_size = provider.ConsumeIntegralInRange<size_t>(0, size);
  std::vector<uint8_t> input_bytes =
      provider.ConsumeBytes<uint8_t>(input_size);
  char* input = reinterpret_cast<char*>(input_bytes.data());

  // Match the regex against the input string.
  struct timespec timeout = {0, 0};
  lmatcher(guts, input, input_size, &timeout, 0);

  // Free the regex guts.
  re_free(guts);

  return 0;
}