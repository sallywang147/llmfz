#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "alias.h"
#include "config/subset.h"
#include "mailbox.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initializing the Mailbox structure
  struct Mailbox m;
  m.magic = stream.ConsumeIntegral<int>();
  m.size = stream.ConsumeIntegral<off_t>();
  m.vsize = stream.ConsumeIntegral<off_t>();
  m.msg_count = stream.ConsumeIntegral<int>();
  m.msg_unread = stream.ConsumeIntegral<int>();
  m.msg_flagged = stream.ConsumeIntegral<int>();
  m.msg_new = stream.ConsumeIntegral<int>();
  m.msg_deleted = stream.ConsumeIntegral<int>();
  m.msg_tagged = stream.ConsumeIntegral<int>();
  m.changed = stream.ConsumeIntegral<int>();
  m.name = stream.ConsumeRandomLengthString().c_str();
  m.flags = stream.ConsumeIntegral<int>();

  // Initializing the ConfigSubset structure
  struct ConfigSubset cs;
  cs.name = stream.ConsumeRandomLengthString().c_str();

  // Call the function to fuzz
  alias_dialog(&m, &cs);

  return 0;
}