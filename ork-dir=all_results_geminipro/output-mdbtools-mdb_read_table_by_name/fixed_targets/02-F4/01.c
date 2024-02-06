#include <fuzzer/FuzzedDataProvider.h>
#include "mdbtools.h"
#include <string>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
#include "mdbtools.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    FuzzedDataProvider stream(Data, Size);
    std::string table_name = stream.ConsumeRandomLengthString();
    mdb_read_table_by_name(mdb, (char *)table_name.c_str(), MDB_TABLE);
    mdb_close(mdb);
  }
  return 0;
}
```

The fixed code is shown below:

```c++
#include <fuzzer/FuzzedDataProvider.h>
#include "mdbtools.h"
#include <string>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  MdbHandle *mdb = mdb_open_buffer((void *)Data, Size, MDB_NOFLAGS);
  if (mdb) {
    FuzzedDataProvider stream(Data, Size);
    std::string table_name = stream.ConsumeRandomLengthString();
    mdb_read_table_by_name(mdb, (char *)table_name.c_str(), MDB_TABLE);
    mdb_close(mdb);
  }
  return 0;
}
```

The `mdbtools.h` header is wrapped with `extern "C" {}` and the `mdb_read_table_by_name` function is declared in the `mdbtools.h` header.