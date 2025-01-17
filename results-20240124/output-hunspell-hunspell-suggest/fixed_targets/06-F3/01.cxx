#include <hunspell/hunspell.hxx>
#include <cstdio>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  Hunspell::Hunspell hunspell;
  hunspell.init("/usr/share/hunspell/en_US.dic", "/usr/share/hunspell/en_US.aff");
  char **suggestions;
  int n = hunspell.spell(&suggestions, (const char *)Data);
  for (int i = 0; i < n; i++) {
    printf("%s\n", suggestions[i]);
    free(suggestions[i]);
  }
  free(suggestions);
  return 0;
}