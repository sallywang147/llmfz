#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <string>

extern "C" int xxxmain(int ac, char ** av);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int ac = stream.ConsumeIntegralInRange<int>(0, 10);
  std::vector<std::string> av_strs;
  std::vector<char*> av;

  for (int i = 0; i < ac; ++i) {
    av_strs.push_back(stream.ConsumeRandomLengthString());
  }

  for (auto& str : av_strs) {
    av.push_back(const_cast<char*>(str.c_str()));
  }

  av.push_back(nullptr); // argv must be null terminated

  xxxmain(ac, av.data());

  return 0;
}