#include <fuzzer/FuzzedDataProvider.h>
#include <hunspell/hunspell.hxx>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static HunspellImpl hunspell;
  FuzzedDataProvider fuzzed_data(data, size);

  // Create a buffer for the word to suggest.
  std::string word = fuzzed_data.ConsumeRandomLengthString();
  char* word_buffer = strdup(word.c_str());
  if (!word_buffer) {
    return 0;
  }

  // Create a buffer for the suggestions list.
  char** suggestions_list = nullptr;

  // Call the target function.
  hunspell.suggest(&suggestions_list, word_buffer);

  // Free the word buffer.
  free(word_buffer);

  // Free each suggestion in the list.
  if (suggestions_list) {
    for (int i = 0; suggestions_list[i] != nullptr; ++i) {
      free(suggestions_list[i]);
    }
    // Free the list itself.
    free(suggestions_list);
  }

  return 0;
}