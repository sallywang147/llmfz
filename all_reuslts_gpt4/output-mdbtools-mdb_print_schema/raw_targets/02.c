#include <fuzzer/FuzzedDataProvider.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mdbtools.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  MdbHandle *mdb = mdb_open_buffer((void *)data, size, MDB_NOFLAGS);
  if (mdb) {
    mdb_read_catalog(mdb, MDB_TABLE);
    if (mdb->num_catalog > 0) {
      MdbCatalogEntry *entry = g_ptr_array_index(mdb->catalog, 0);
      MdbTableDef *table = mdb_read_table(entry);
      if (table) {
        mdb_read_columns(table);
        mdb_rewind_table(table);
        while (mdb_fetch_row(table))
          ;
        int export_options = stream.ConsumeIntegral<int>();
        FILE *outfile = tmpfile();
        if (outfile) {
          mdb_print_schema(mdb, outfile, table->name, NULL, export_options);
          fclose(outfile);
        }
        mdb_free_tabledef(table);
      }
    }
    mdb_close(mdb);
  }
  return 0;
}