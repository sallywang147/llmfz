#include <fuzzer/FuzzedDataProvider.h>
#include "libyang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lysp_ctx ctx = {0};
  struct lysp_stmt stmt = {0};
  struct lysp_node parent = {0};
  struct lysp_node *siblings = nullptr;

  // Consume data for the stmt
  stmt.keyword = stream.ConsumeRandomLengthString().c_str();
  stmt.arg = stream.ConsumeRandomLengthString().c_str();
  stmt.flags = stream.ConsumeIntegral<uint16_t>();

  // Consume data for the parent
  parent.name = stream.ConsumeRandomLengthString().c_str();
  parent.dsc = stream.ConsumeRandomLengthString().c_str();
  parent.ref = stream.ConsumeRandomLengthString().c_str();
  parent.flags = stream.ConsumeIntegral<uint16_t>();

  // Call the function to fuzz
  lysp_stmt_list(&ctx, &stmt, &parent, &siblings);

  return 0;
}