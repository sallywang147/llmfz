#include <dlfcn.h>
#include <execinfo.h>

extern "C" {
#include <libunwind.h>
}

int main() {
  void *handle = dlopen("libfoo.so", RTLD_NOW);
  if (!handle) {
    return -1;
  }

  void (*func)() = (void (*)())dlsym(handle, "foo");
  if (!func) {
    return -1;
  }

  func();

  dlclose(handle);

  return 0;
}