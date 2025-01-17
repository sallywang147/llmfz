#include <dlfcn.h>
#include <libunwind.h>

extern "C" {
#include <libdwfl.h>
}

int main() {
  void *handle = dlopen("libfoo.so", RTLD_NOW);
  if (!handle) {
    return -1;
  }

  unw_context_t uc;
  unw_getcontext(&uc);

  Dwfl_Callbacks callbacks;
  Dwfl_Callbacks_init(&callbacks, DWFL_CB_DEFAULT);

  Dwfl *dwfl = dwfl_begin(&callbacks);
  if (!dwfl) {
    return -1;
  }

  int err = dwfl_report_unwind(dwfl, &uc, NULL, NULL);
  if (err != 0) {
    return -1;
  }

  dwfl_end(dwfl);
  dlclose(handle);

  return 0;
}