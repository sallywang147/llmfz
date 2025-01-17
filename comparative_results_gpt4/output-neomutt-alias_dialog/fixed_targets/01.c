#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "alias.h"
#include "config/config.h"
#include "mailbox.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize Mailbox
  struct Mailbox *mbox = mailbox_new();
  mbox->name = stream.ConsumeRandomLengthString().c_str();

  // Initialize ConfigSubset
  struct ConfigSubset *sub = cs_new(NULL);
  sub->name = stream.ConsumeRandomLengthString().c_str();

  // Call the target function
  alias_dialog(mbox, sub);

  // Cleanup
  mailbox_free(&mbox);
  cs_free(&sub);

  return 0;
}