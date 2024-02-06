#include <fuzzer/FuzzedDataProvider.h>
#include <hunspell.hxx>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string word = stream.ConsumeRandomLengthString();
  char **slst;

  Hunspell hunspell("en_US.aff", "en_US.dic");
  hunspell.suggest(&slst, const_cast<char *>(word.c_str()));

  // Free memory allocated by suggest
  hunspell.free_list(&slst, 0);

  return 0;
}