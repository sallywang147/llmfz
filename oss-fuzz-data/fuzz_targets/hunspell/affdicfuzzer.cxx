/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include <fstream>
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

  if (!dict.spell(word))
    dict.suggest(word);

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

    if (!dict.spell(word))
        dict.suggest(word);

    return 0;
}
#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
