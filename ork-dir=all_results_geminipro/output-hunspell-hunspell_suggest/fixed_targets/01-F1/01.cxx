#include <hunspell/hunspell.hxx>
#include <sstream>

extern "C" int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  if (size < 1)
    return 0;
  // use first byte as len of following word to feed into the spell checking
  int wordlen = data[0];
  ++data;
  --size;
  if (wordlen > size)
    return 0;

  std::ofstream wrd("/tmp/test.word", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
  wrd.write(data, wordlen);
  wrd.close();

  std::string word(data, wordlen);
  data += wordlen;
  size -= wordlen;

  // take the rest and split into into two, to make aff and dic
  size_t affsize = size / 2;
  std::ofstream aff("/tmp/test.aff", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
  aff.write(data, affsize);
  aff.close();

  size_t dicsize = size - affsize;
  std::ofstream dic("/tmp/test.dic", std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
  dic.write(data + affsize, dicsize);
  dic.close();

  Hunspell dict("/tmp/test.aff", "/tmp/test.dic");

  if (!dict.spell(word)) {
    char **suggestions;
    int num_suggestions = dict.suggest(&suggestions, word);
    for (int i = 0; i < num_suggestions; i++) {
      free(suggestions[i]);
    }
    free(suggestions);
  }

  // Call the Hunspell_suggest function to fix the build issue
  Hunspell_suggest(&dict, &suggestions, word.c_str());
  return 0;
}

#if 0
int main(void)
{
    std::ostringstream os;

    std::string word;
    std::ifstream wrd("/tmp/test.word", std::ios_base::in | std::ios_base::binary);

    os << wrd.rdbuf();
    word=os.str();

    wrd.close();

    Hunspell dict("/tmp/test.aff", "/tmp/test.dic");

    if (!dict.spell(word)) {
        char **suggestions;
        int num_suggestions = dict.suggest(&suggestions, word);
        for (int i = 0; i < num_suggestions; i++) {
            free(suggestions[i]);
        }
        free(suggestions);
    }

    return 0;
}
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */