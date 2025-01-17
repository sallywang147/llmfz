#include <fuzzer/FuzzedDataProvider.h>
#include <libdwfl.h>
#include <stdint.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  Dwfl *dwfl = dwfl_begin();
  if (!dwfl)
    return 0;

  Dwfl_Thread *thread = dwfl_getthread_byid(dwfl, fdp.ConsumeIntegral<int>());
  if (!thread)
    return 0;

  char *arg = fdp.ConsumeBytesAsString(fdp.ConsumeIntegralInRange(0, 1024)).c_str();
  get_one_thread_frames_cb(thread, arg);
  dwfl_end(dwfl);
  return 0;
}