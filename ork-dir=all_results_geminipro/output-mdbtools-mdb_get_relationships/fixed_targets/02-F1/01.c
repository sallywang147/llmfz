#include "mdbtools.h"

extern "C" {
#include <stddef.h>
#include <stdint.h>
#include <string.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    FuzzedDataProvider provider(Data, Size);
    std::string dbnamespace = provider.ConsumeRemainingBytesAsString();
    std::string tablename = provider.ConsumeRemainingBytesAsString();
    mdb_get_relationships(mdb, dbnamespace.c_str(), tablename.c_str());
    mdb_close(mdb);
  }
  return 0;
}