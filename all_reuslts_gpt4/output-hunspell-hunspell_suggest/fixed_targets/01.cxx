#include <fuzzer/FuzzedDataProvider.h>
#include <hunspell/hunspell.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  std::string word = provider.ConsumeRandomLengthString();
  if (word.empty()) {
    return 0;
  }

  Hunhandle* handle = Hunspell_create("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");
  if (handle == nullptr) {
    return 0;
  }

  char** suggestions;
  int num_suggestions = Hunspell_suggest(handle, &suggestions, const_cast<char*>(word.c_str()));

  for (int i = 0; i < num_suggestions; ++i) {
    free(suggestions[i]);
  }
  free(suggestions);

  Hunspell_destroy(handle);

  return 0;
}