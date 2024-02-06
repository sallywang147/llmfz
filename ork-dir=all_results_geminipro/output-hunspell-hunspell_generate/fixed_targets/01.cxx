#include <Hunspell.h>
#include <fstream>
#include <string>
#include <cstring>

extern "C" {
#include <hunspell.h>
}

int split_data(const char *data, size_t size) {
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

  char **suggestions;

  int ret = Hunspell_suggest(&dict, &suggestions, word.c_str(), nullptr);
  if (ret)
    return ret;

  for (int i = 0; suggestions[i]; ++i) {
    free(suggestions[i]);
  }
  free(suggestions);

  return 0;
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */