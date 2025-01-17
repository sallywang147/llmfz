#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

extern "C" int xxxmain(int ac, char ** av);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int ac = stream.ConsumeIntegralInRange<int>(1, 10);
  std::vector<std::string> av_strings;
  std::vector<char*> av;

  for (int i = 0; i < ac; ++i) {
    av_strings.push_back(stream.ConsumeRandomLengthString());
  }

  for (auto& s : av_strings) {
    av.push_back(const_cast<char*>(s.c_str()));
  }

  xxxmain(ac, av.data());

  return 0;
}