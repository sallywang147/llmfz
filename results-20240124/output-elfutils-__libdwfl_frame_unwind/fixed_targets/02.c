#include <dlfcn.h>
#include <execinfo.h>
#include <iostream>

extern "C" {
#include <libdwarf.h>
#include <libdwarf/dwarf.h>
#include <libdwarf/libdwarf.h>
}

int main() {
  void *handle = dlopen("libdwarf.so", RTLD_NOW);
  if (handle == nullptr) {
    std::cerr << "Failed to load libdwarf.so" << std::endl;
    return 1;
  }

  Dwarf_Debug dbg = dwarf_begin(handle, DWARF_C_READ, nullptr, nullptr, nullptr);
  if (dbg == nullptr) {
    std::cerr << "Failed to initialize libdwarf" << std::endl;
    return 1;
  }

  // ... use libdwarf ...

  dwarf_end(dbg);
  dlclose(handle);

  return 0;
}