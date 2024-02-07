#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "alias.h"
#include "config/subset.h"
#include "mailbox/mailbox.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Mailbox *mailbox = mutt_mailbox_new();
  struct ConfigSubset *subset = cs_subset_new();

  alias_dialog(mailbox, subset);

  mutt_mailbox_free(&mailbox);
  cs_subset_free(&subset);

  return 0;
}