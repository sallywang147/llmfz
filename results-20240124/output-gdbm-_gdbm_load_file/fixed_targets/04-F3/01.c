#include <gdbm-ndbm.h>
#include <string.h>

extern "C" {
#include "libFuzzer.h"
}

struct gdbm_file_info;
struct dump_file;

extern "C" int gdbm_init(const void *data, size_t size);
extern "C" int _gdbm_load_file(struct dump_file *file, struct gdbm_file_info *dbf,
                               struct gdbm_file_info **ofp, int replace, int meta_mask);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct dump_file file;
  struct gdbm_file_info dbf;
  struct gdbm_file_info *ofp;
  int replace = 0;
  int meta_mask = 0;

  gdbm_init(data, size);
  _gdbm_load_file(&file, &dbf, &ofp, replace, meta_mask);
  return 0;
}