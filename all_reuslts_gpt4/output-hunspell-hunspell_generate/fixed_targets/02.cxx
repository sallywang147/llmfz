#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "hunspell/hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  
  // Create a Hunspell object
  Hunhandle *hunspell = Hunspell_create("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");
  if (!hunspell) {
    return 0;
  }

  // Extract the word and pattern
  std::string word = stream.ConsumeRandomLengthString();
  std::string pattern = stream.ConsumeRemainingBytesAsString();

  // Generate the list of words
  char **slst = nullptr;
  int numWords = Hunspell_generate(hunspell, &slst, const_cast<char *>(word.c_str()), const_cast<char *>(pattern.c_str()));

  // Free the generated words
  for (int i = 0; i < numWords; i++) {
    free(slst[i]);
  }
  free(slst);

  // Destroy the Hunspell object
  Hunspell_destroy(hunspell);

  return 0;
}