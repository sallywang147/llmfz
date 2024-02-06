#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "hunspell/hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize Hunspell
  Hunhandle* hunspell = Hunspell_create("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");
  if (!hunspell) {
    return 0;
  }

  // Consume fuzzing data to create a word
  std::string word = stream.ConsumeRandomLengthString();
  
  // Initialize slst for suggestions
  char** slst = nullptr;

  // Call Hunspell_suggest
  int num_suggestions = Hunspell_suggest(hunspell, &slst, const_cast<char*>(word.c_str()));

  // Free memory allocated by Hunspell_suggest
  for (int i = 0; i < num_suggestions; i++) {
    free(slst[i]);
  }
  free(slst);

  // Destroy Hunspell
  Hunspell_destroy(hunspell);

  return 0;
}