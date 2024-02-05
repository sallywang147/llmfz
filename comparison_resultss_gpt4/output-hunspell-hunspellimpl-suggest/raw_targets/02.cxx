#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "hunspell/hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }
  
  FuzzedDataProvider stream(data, size);

  std::string word = stream.ConsumeRandomLengthString();
  char *c_word = const_cast<char *>(word.c_str());

  HunspellImpl hunspell;
  char **suggestions;

  hunspell.suggest(&suggestions, c_word);

  return 0;
}