#include <dlfcn.h>
#include <execinfo.h>

extern "C" {
#include <libunwind.h>
}

void __libdwfl_frame_unwind(struct Dwfl_Frame * state) {
  // Do something
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