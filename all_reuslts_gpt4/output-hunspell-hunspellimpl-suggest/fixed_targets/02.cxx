#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Hunspell
  HunspellImpl hunspell;

  // Consume data to create a word
  std::string word = stream.ConsumeRandomLengthString();
  char *word_ptr = const_cast<char *>(word.c_str());

  // Initialize slst
  char ***slst = (char ***)malloc(sizeof(char **));
  *slst = nullptr;

  // Call the target function
  hunspell.suggest(&hunspell, slst, word_ptr);

  // Free the suggested words
  if (*slst) {
    for (int i = 0; (*slst)[i] != nullptr; i++) {
      free((*slst)[i]);
    }
    free(*slst);
  }

  // Free the slst
  free(slst);

  return 0;
}