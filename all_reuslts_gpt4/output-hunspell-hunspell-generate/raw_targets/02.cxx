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
  Hunspell hunspell("en_US.aff", "en_US.dic");

  // Generate words and patterns
  std::string word = stream.ConsumeRandomLengthString();
  std::string pattern = stream.ConsumeRemainingBytesAsString();

  // Generate slst
  char** slst = nullptr;

  // Call the target function
  hunspell.generate(&slst, word.c_str(), pattern.c_str());

  // Free the generated slst
  if (slst) {
    for (int i = 0; slst[i] != nullptr; i++) {
      free(slst[i]);
    }
    free(slst);
  }

  return 0;
}