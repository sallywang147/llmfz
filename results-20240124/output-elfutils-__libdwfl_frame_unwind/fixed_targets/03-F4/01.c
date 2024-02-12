#include <libunwind.h>
#include <dlfcn.h>

extern "C" {
#include <libdwfl.h>
}

void __libdwfl_frame_unwind(struct Dwfl_Frame * state) {}

int main() {
  unw_context_t uc;
  unw_getcontext(&uc);
  unw_cursor_t cursor;
  unw_init_local(&cursor, &uc);
  int i = 0;
  while (unw_step(&cursor) > 0) {
    Dl_info info;
    int ret = dladdr(unw_get_reg(&cursor, UNW_REG_IP), &info);
    if (ret == 0) {
      printf("failed to get dladdr\n");
      continue;
    }
    printf("%d: %s\n", i++, info.dli_sname);
  }
  return 0;
}