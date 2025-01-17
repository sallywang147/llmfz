#include <hunspell/hunspell.hxx>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  Hunspell::Dict *dict = Hunspell::Dict::create("/usr/share/hunspell/en_US.dic", "/usr/share/hunspell/en_US.aff");
  char **suggestions;
  int n = dict->suggest(&suggestions, (const char *)Data);
  for (int i = 0; i < n; i++) {
    printf("%s\n", suggestions[i]);
    free(suggestions[i]);
  }
  free(suggestions);
  return 0;
}