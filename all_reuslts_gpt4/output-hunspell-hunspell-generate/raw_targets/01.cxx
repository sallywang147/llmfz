#include <fuzzer/FuzzedDataProvider.h>
#include <hunspell/hunspell.hxx>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 3) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  Hunspell hunspell;

  std::string word = fuzzed_data.ConsumeRandomLengthString();
  std::string pattern = fuzzed_data.ConsumeRemainingBytesAsString();

  char **slst = nullptr;

  hunspell.generate(&slst, word.c_str(), pattern.c_str());

  if (slst) {
    hunspell.free_list(&slst, 0);
  }

  return 0;
}