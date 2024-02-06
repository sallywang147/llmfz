#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "hunspell.hxx"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  Hunspell hunspell("en_US.aff", "en_US.dic");

  std::string word = stream.ConsumeRemainingBytesAsString();
  char **slst;

  hunspell.suggest(&slst, word.c_str());

  return 0;
}