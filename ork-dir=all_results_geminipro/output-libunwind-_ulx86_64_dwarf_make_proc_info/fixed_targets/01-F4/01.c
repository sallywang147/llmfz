#include <libunwind.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <dwarf.h>
#include <libdwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  unw_cursor_t cursor;
  unw_context_t uc;

  unw_getcontext(&uc);
  unw_init_local(&cursor, &uc);

  while (unw_step(&cursor) > 0) {
    dwarf_cursor_t dwarf_cursor;
    unw_get_dwarf_cursor(&cursor, &dwarf_cursor);
    _ULx86_64_dwarf_make_proc_info(&dwarf_cursor);
  }

  return 0;
}