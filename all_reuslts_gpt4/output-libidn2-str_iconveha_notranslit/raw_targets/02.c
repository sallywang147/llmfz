#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" char * str_iconveha_notranslit(char * src, char * from_codeset, char * to_codeset, int handler);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Split the input data into four parts.
  size_t src_size = stream.remaining_bytes() / 4;
  size_t from_codeset_size = stream.remaining_bytes() / 4;
  size_t to_codeset_size = stream.remaining_bytes() / 4;
  size_t handler_size = stream.remaining_bytes() - src_size - from_codeset_size - to_codeset_size;

  // Consume the data from the stream.
  std::string src = stream.ConsumeBytesAsString(src_size);
  std::string from_codeset = stream.ConsumeBytesAsString(from_codeset_size);
  std::string to_codeset = stream.ConsumeBytesAsString(to_codeset_size);
  int handler = stream.ConsumeIntegral<int>();

  // Call the function to fuzz.
  char* result = str_iconveha_notranslit(const_cast<char*>(src.c_str()), const_cast<char*>(from_codeset.c_str()), const_cast<char*>(to_codeset.c_str()), handler);

  // Free the memory allocated by the function.
  if (result != nullptr) {
    free(result);
  }

  return 0;
}