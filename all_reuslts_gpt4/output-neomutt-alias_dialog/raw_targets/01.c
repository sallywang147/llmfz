#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "mutt/alias.h"
#include "mutt/mailbox.h"
#include "mutt/subset.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the Mailbox structure
  struct Mailbox m;
  m.magic = stream.ConsumeIntegral<enum MailboxType>();
  m.size = stream.ConsumeIntegral<uint64_t>();
  m.path = stream.ConsumeRandomLengthString().c_str();
  m.name = stream.ConsumeRandomLengthString().c_str();

  // Initialize the ConfigSubset structure
  struct ConfigSubset cs;
  cs.name = stream.ConsumeRandomLengthString().c_str();
  cs.sub = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  alias_dialog(&m, &cs);

  return 0;
}