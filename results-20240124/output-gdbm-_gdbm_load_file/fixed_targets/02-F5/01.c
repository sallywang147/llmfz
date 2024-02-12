#include <gdbm-ndbm.h>
extern "C" {
#include <gdbm/ndbm.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct dump_file file;
  struct gdbm_file_info dbf;
  struct gdbm_file_info *ofp;
  int replace = 0;
  int meta_mask = 0;
  _gdbm_load_file(&file, &dbf, &ofp, replace, meta_mask);
  return 0;
}