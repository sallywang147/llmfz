#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" char * str_iconveha_notranslit(char * src, char * from_codeset, char * to_codeset, int handler);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Consume the data to generate the parameters for the function
  std::string src = stream.ConsumeRandomLengthString();
  std::string from_codeset = stream.ConsumeRandomLengthString();
  std::string to_codeset = stream.ConsumeRandomLengthString();
  int handler = stream.ConsumeIntegral<int>();

  // Call the function with the generated parameters
  char * result = str_iconveha_notranslit(const_cast<char*>(src.c_str()), const_cast<char*>(from_codeset.c_str()), const_cast<char*>(to_codeset.c_str()), handler);

  // Free the memory allocated by the function
  if (result != nullptr) {
    free(result);
  }

  return 0;
}