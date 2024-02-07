#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an instance of HunspellImpl
  HunspellImpl* hunspellImpl = new HunspellImpl();

  // Extract a string for the word parameter
  std::string word = stream.ConsumeRandomLengthString();
  
  // Initialize slst to null
  char ***slst = nullptr;

  // Call the suggest method
  hunspellImpl->suggest(slst, const_cast<char*>(word.c_str()));

  // Free the memory allocated for the suggestions
  if (slst) {
    for (int i = 0; (*slst)[i] != nullptr; i++) {
      free((*slst)[i]);
    }
    free(*slst);
  }

  delete hunspellImpl;

  return 0;
}