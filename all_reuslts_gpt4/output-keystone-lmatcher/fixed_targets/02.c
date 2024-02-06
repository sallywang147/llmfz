#include <fuzzer/FuzzedDataProvider.h>
#include <regex.h>
#include <time.h>
#include <cstdint>
#include <cstddef>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  int cflags = stream.ConsumeIntegral<int>();
  regex_t preg;
  regcomp(&preg, ".*", cflags);

  struct re_guts* g = preg.re_g;
  if (g == NULL) {
    return 0;
  }

  std::string str = stream.ConsumeRemainingBytesAsString();
  char* string = const_cast<char*>(str.c_str());
  size_t n = str.size();

  struct timespec timeout;
  timeout.tv_sec = 0;
  timeout.tv_nsec = 0;

  int err = lmatcher(g, string, n, &timeout, 0);

  regfree(&preg);

  return 0;
}