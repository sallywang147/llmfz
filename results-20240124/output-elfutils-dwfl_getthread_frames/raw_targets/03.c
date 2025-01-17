 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <dwfl.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const char* library_path = stream.ConsumeRemainingBytesAsString().c_str();
  void* handle = dlopen(library_path, RTLD_LAZY);
  if (handle == nullptr) {
    return 0;
  }

  struct Dwfl* dwfl = dwfl_begin();
  if (dwfl == nullptr) {
    dlclose(handle);
    return 0;
  }

  int tid = stream.ConsumeIntegral<int>();
  int ret = dwfl_getthread_frames(dwfl, tid, nullptr, nullptr);
  if (ret != DWFL_E_NOERROR) {
    dwfl_end(dwfl);
    dlclose(handle);
    return 0;
  }

  dwfl_end(dwfl);
  dlclose(handle);
  return 0;
}