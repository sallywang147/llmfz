#include <fuzzer/FuzzedDataProvider.h>
#include "mdbtools.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  MdbHandle *mdb = mdb_open_buffer((void *)data, size, MDB_NOFLAGS);
  if (mdb) {
    size_t remaining_size = provider.remaining_bytes();
    std::string dbnamespace = provider.ConsumeBytesAsString(remaining_size / 2);
    std::string tablename = provider.ConsumeRemainingBytesAsString();

    char *relationships = mdb_get_relationships(mdb, (char *)dbnamespace.c_str(), (char *)tablename.c_str());
    if (relationships) {
      free(relationships);
    }

    mdb_close(mdb);
  }

  return 0;
}