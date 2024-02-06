#include <mdbtools.h>
#include <sstream>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    FuzzedDataProvider stream(Data, Size);
    std::string table_name = stream.ConsumeRemainingBytesAsString();
    struct S_MdbTableDef *table =
        mdb_read_table_by_name(mdb, (char *)table_name.c_str(), MDB_TABLE);
    if (table) {
      mdb_read_columns(table);
      mdb_rewind_table(table);
      while (mdb_fetch_row(table))
        ;
      mdb_free_tabledef(table);
    }
    mdb_close(mdb);
  }
  return 0;
}