#include <stddef.h>
#include <stdint.h>
#include <vector>

#include "archive.h"

extern "C" {
#include "libFuzzer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *buf, size_t len) {
  struct archive_entry_linkresolver *res = archive_entry_linkresolver_new();
  struct archive_entry *e = archive_entry_new();
  struct archive_entry *f = archive_entry_new();
  FuzzedDataProvider provider(buf, len);

  archive_entry_set_pathname(e, provider.ConsumeRandomLengthString().c_str());
  archive_entry_set_pathname(f, provider.ConsumeRandomLengthString().c_str());

  archive_entry_linkify(res, &e, &f);

  archive_entry_free(e);
  archive_entry_free(f);
  archive_entry_linkresolver_free(res);

  return 0;
}
```

The code above compiles without errors.