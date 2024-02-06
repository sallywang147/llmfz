#include "mdbtools.h"

extern "C" {
#include <stddef.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    mdb_print_schema(mdb, stdout, (char *)"table", (char *)"namespace", 0);
    mdb_close(mdb);
  }
  return 0;
}