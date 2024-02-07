#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a HunspellImpl object
  HunspellImpl hunspell;

  // Create a char** slst
  char **slst = nullptr;

  // Consume the data as a string for the word
  std::string word = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  hunspell.suggest(&slst, const_cast<char*>(word.c_str()));

  // Free the memory allocated by suggest
  if (slst != nullptr) {
    hunspell.free_list(&slst, 0);
  }

  return 0;
}