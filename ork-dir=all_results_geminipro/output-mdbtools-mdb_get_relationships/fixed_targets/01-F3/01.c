#include "mdbtools.h"

extern "C" {
#include <string>
#include <fstream>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    FuzzedDataProvider stream(Data, Size);
    std::string dbnamespace = stream.ConsumeRemainingBytesAsString();
    std::string tablename = stream.ConsumeRemainingBytesAsString();
    mdb_get_relationships(mdb, dbnamespace.c_str(), tablename.c_str());
    mdb_close(mdb);
  }
  return 0;
}