#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string input = stream.ConsumeRemainingBytesAsString();
  char* input_cstr = const_cast<char*>(input.c_str());

  const std::string from_codeset = stream.ConsumeRandomLengthString();
  char* from_codeset_cstr = const_cast<char*>(from_codeset.c_str());

  const std::string to_codeset = stream.ConsumeRandomLengthString();
  char* to_codeset_cstr = const_cast<char*>(to_codeset.c_str());

  const int handler = stream.ConsumeIntegral<int>();

  char* output = str_iconveha_notranslit(input_cstr, from_codeset_cstr,
                                         to_codeset_cstr, handler);
  free(output);

  return 0;
}