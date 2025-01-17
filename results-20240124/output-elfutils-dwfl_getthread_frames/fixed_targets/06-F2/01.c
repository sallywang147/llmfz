#include <assert.h>
extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <dwfl.h>
}
#include <fuzzer/FuzzedDataProvider.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int tid = stream.ConsumeIntegral<int>();
  std::string arg = stream.ConsumeRemainingBytesAsString();
  dwfl_getthread_frames(nullptr, tid, nullptr, const_cast<char*>(arg.c_str()));
  return 0;
}