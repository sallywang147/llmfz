#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <sys/dir.h>

extern "C" {
#include <algorithm>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const int flags = stream.ConsumeIntegral<int>();
  const size_t name_size = stream.ConsumeIntegralInRange<size_t>(0, size);
  char* name = static_cast<char*>(malloc(name_size + 1));
  stream.ConsumeBytes(name, name_size);
  name[name_size] = '\0';
  struct __dirstream* dir_stream;
  opendirat(fd, name, flags, &dir_stream);
  free(name);
  return 0;
}