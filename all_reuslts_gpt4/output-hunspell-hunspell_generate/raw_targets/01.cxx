#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hunspell/hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  Hunhandle* hunspell = Hunspell_create("/usr/share/hunspell/en_US.aff", "/usr/share/hunspell/en_US.dic");
  if (hunspell == nullptr) {
    return 0;
  }

  std::string word = provider.ConsumeRandomLengthString();
  std::string pattern = provider.ConsumeRemainingBytesAsString();

  char** slst = nullptr;

  Hunspell_generate(hunspell, &slst, const_cast<char*>(word.c_str()), const_cast<char*>(pattern.c_str()));

  if (slst != nullptr) {
    Hunspell_free_list(hunspell, &slst, 0);
  }

  Hunspell_destroy(hunspell);

  return 0;
}