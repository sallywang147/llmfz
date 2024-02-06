#include <fuzzer/FuzzedDataProvider.h>
#include <libdwarf.h>
#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  Dwfl_Thread *thread = dwfl_thread_init(NULL, NULL, 0);
  if (thread == NULL) {
    return 0;
  }

  func_type callback = [](Dwfl_Module *mod, Dwfl_Func *func, void *arg) {
    (void)mod;
    (void)func;
    (void)arg;
    return 0;
  };

  dwfl_thread_getframes(thread, callback, NULL);

  dwfl_thread_destroy(thread);

  return 0;
}