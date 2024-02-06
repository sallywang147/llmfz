#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" char * str_iconveha(char * src, char * from_codeset, char * to_codeset, bool transliterate, int handler);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string src = stream.ConsumeRandomLengthString();
  std::string from_codeset = stream.ConsumeRandomLengthString();
  std::string to_codeset = stream.ConsumeRandomLengthString();
  bool transliterate = stream.ConsumeBool();
  int handler = stream.ConsumeIntegral<int>();

  char * result = str_iconveha(const_cast<char*>(src.c_str()), const_cast<char*>(from_codeset.c_str()), const_cast<char*>(to_codeset.c_str()), transliterate, handler);

  if (result != NULL) {
    free(result);
  }

  return 0;
}