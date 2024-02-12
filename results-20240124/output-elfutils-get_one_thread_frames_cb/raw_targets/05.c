 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <dwfl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  Dwfl *dwfl = dwfl_begin();
  if (dwfl == NULL) {
    return 0;
  }

  char *arg = reinterpret_cast<char*>(provider.ConsumeBytes<uint8_t>(size).data());
  Dwfl_Thread *thread = dwfl_get_thread(dwfl, 0);
  if (thread == NULL) {
    dwfl_end(dwfl);
    return 0;
  }

  int ret = get_one_thread_frames_cb(thread, arg);
  dwfl_end(dwfl);

  return ret;
}