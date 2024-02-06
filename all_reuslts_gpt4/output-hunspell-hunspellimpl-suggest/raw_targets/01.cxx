#include <fuzzer/FuzzedDataProvider.h>
#include <hunspell/hunspell.hxx>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize Hunspell
  HunspellImpl hunspell;

  // Generate word from fuzzer data
  std::string word = stream.ConsumeRandomLengthString();
  char* c_word = const_cast<char*>(word.c_str());

  // Initialize slst
  char*** slst = (char***) malloc(sizeof(char**));
  *slst = NULL;

  // Call the target function
  hunspell.suggest(slst, c_word);

  // Free the allocated memory
  if (*slst) {
    for (int i = 0; (*slst)[i] != NULL; ++i) {
      free((*slst)[i]);
    }
    free(*slst);
  }
  free(slst);

  return 0;
}