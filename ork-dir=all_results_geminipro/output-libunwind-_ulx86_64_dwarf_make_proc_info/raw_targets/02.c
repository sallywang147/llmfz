#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "libunwind.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const uint8_t cursor_version = stream.ConsumeIntegral<uint8_t>();
  const uint8_t cursor_address_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t cursor_format = stream.ConsumeIntegral<uint8_t>();
  const uint64_t cursor_gpreg_count = stream.ConsumeIntegral<uint64_t>();
  const uint64_t cursor_fpreg_count = stream.ConsumeIntegral<uint64_t>();
  const uint64_t cursor_exreg_count = stream.ConsumeIntegral<uint64_t>();
  const uint64_t cursor_valist_count = stream.ConsumeIntegral<uint64_t>();
  const uint64_t cursor_loc_count = stream.ConsumeIntegral<uint64_t>();
  const uint64_t cursor_ranges_count = stream.ConsumeIntegral<uint64_t>();
  const uint64_t cursor_cie_id = stream.ConsumeIntegral<uint64_t>();

  unw_cursor_t cursor;
  unw_init_local(&cursor, cursor_version);
  cursor.dwarf.address_size = cursor_address_size;
  cursor.dwarf.format = cursor_format;
  cursor.dwarf.gpreg_count = cursor_gpreg_count;
  cursor.dwarf.fpreg_count = cursor_fpreg_count;
  cursor.dwarf.exreg_count = cursor_exreg_count;
  cursor.dwarf.valist_count = cursor_valist_count;
  cursor.dwarf.loc_count = cursor_loc_count;
  cursor.dwarf.ranges_count = cursor_ranges_count;
  cursor.dwarf.cie_id = cursor_cie_id;

  _ULx86_64_dwarf_make_proc_info(&cursor);

  return 0;
}