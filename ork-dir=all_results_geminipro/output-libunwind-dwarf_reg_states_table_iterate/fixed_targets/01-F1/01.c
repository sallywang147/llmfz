#include <fuzzer/FuzzedDataProvider.h>

#include <dwarf.h>
#include <stddef.h>
#include <stdint.h>

extern "C" {
#include <libdwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a fake DWARF cursor.
  struct dwarf_cursor cursor;
  cursor.cu_length = stream.ConsumeIntegral<uint32_t>();
  cursor.cu_offset = stream.ConsumeIntegral<uint32_t>();
  cursor.section_offset = stream.ConsumeIntegral<uint32_t>();
  cursor.end_section = stream.ConsumeIntegral<uint32_t>();
  cursor.image_base = stream.ConsumeIntegral<uint64_t>();

  // Create a fake callback function.
  int callback(struct dwarf_reg_state_table* table, void* arg) {
    return 0;
  }

  // Call the function to be fuzzed.
  dwarf_reg_states_table_iterate(&cursor, callback, nullptr);

  return 0;
}