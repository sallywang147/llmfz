#include <iostream>
#include <dlfcn.h>

extern "C" {
#include <libdwarf.h>
#include <libunwind.h>
}

int main() {
  void *handle = dlopen("libdwfl.so", RTLD_NOW);
  if (!handle) {
    std::cerr << "Error: " << dlerror() << std::endl;
    return 1;
  }

  Dwarf_Debug dbg = dwarf_begin(handle, DWARF_C_READ, nullptr);
  if (!dbg) {
    std::cerr << "Error: " << dwarf_errmsg(dwarf_errno(dbg)) << std::endl;
    return 1;
  }

  Dwarf_Die die;
  int res = dwarf_next_cu_header(dbg, &die, nullptr, nullptr, nullptr);
  if (res != DW_DLV_OK) {
    std::cerr << "Error: " << dwarf_errmsg(res) << std::endl;
    return 1;
  }

  Dwarf_Addr low_pc = 0;
  Dwarf_Addr high_pc = 0;
  res = dwarf_get_cu_die_range(die, &low_pc, &high_pc);
  if (res != DW_DLV_OK) {
    std::cerr << "Error: " << dwarf_errmsg(res) << std::endl;
    return 1;
  }

  std::cout << "Low PC: " << low_pc << std::endl;
  std::cout << "High PC: " << high_pc << std::endl;

  dwarf_end(dbg);
  dlclose(handle);

  return 0;
}