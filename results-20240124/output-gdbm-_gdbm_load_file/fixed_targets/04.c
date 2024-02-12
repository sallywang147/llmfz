#include <gdbm.h>

extern "C" int gdbm_init(const void *data, size_t size) {
  // ...
}

extern "C" int _gdbm_load_file(struct dump_file *file, struct gdbm_file_info *dbf, struct gdbm_file_info **ofp, int replace, int meta_mask) {
  // ...
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  gdbm_init(data, size);
  // ...
  _gdbm_load_file(file, dbf, ofp, replace, meta_mask);
  // ...
}