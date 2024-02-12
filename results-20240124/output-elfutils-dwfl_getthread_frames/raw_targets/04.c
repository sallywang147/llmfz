 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>
#include <dwfl.h>
#include <sys/types.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int thread_id = stream.ConsumeIntegral<int>();
  const char* arg = stream.ConsumeRemainingBytesAsString().c_str();

  Dwfl* dwfl = dwfl_begin();
  if (dwfl == nullptr) {
    return 0;
  }

  dwfl_getthread_frames(dwfl, thread_id, nullptr, const_cast<char*>(arg));

  dwfl_end(dwfl);
  return 0;
}