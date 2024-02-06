#include "mdbtools.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    mdb_dump_catalog(mdb, MDB_TABLE);
    mdb_close(mdb);
  }
  return 0;
}