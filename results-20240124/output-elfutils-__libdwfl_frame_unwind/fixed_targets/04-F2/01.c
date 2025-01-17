#include <libdwfl.h>

extern "C" {
#include <dlfcn.h>
#include <link.h>
}

int main() {
  void *handle = dlopen(nullptr, RTLD_NOW);
  if (handle == nullptr) {
    return 1;
  }

  dl_iterate_phdr(handle, [](struct dl_phdr_info *info, size_t, void *) {
    char *base = reinterpret_cast<char *>(info->dlpi_addr);
    for (ElfW(Addr) addr = info->dlpi_addr; addr < info->dlpi_addr + info->dlpi_memsz;
         addr += DW_CFA_STACK_SIZE) {
      __libdwfl_frame_unwind(base, addr, nullptr);
    }
    return 0;
  }, nullptr);

  dlclose(handle);
  return 0;
}