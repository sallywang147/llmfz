#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libyang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the context
  struct lysp_ctx pctx;
  pctx.ctx = ly_ctx_new(NULL, 0);
  pctx.pmod = (struct lysp_module *)calloc(1, sizeof *pctx.pmod);
  pctx.pmod->name = "fuzz";
  pctx.pmod->revision = "2018-05-21";

  // Initialize the extension instance
  struct lysp_ext_instance ext;
  ext.name = (char *)stream.ConsumeRandomLengthString().c_str();
  ext.argument = (char *)stream.ConsumeRandomLengthString().c_str();
  ext.parent_stmt_type = stream.ConsumeIntegralInRange<uint16_t>(0, UINT16_MAX);
  ext.parent_stmt_index = stream.ConsumeIntegralInRange<uint16_t>(0, UINT16_MAX);
  ext.format = stream.ConsumeIntegralInRange<LY_VALUE_FORMAT>(0, LY_VALUE_FORMAT_SIZE - 1);
  ext.prefix_data = (void *)stream.ConsumeRandomLengthString().c_str();

  // Call the function to fuzz
  int result = structure_aug_parse(&pctx, &ext);

  // Clean up
  ly_ctx_destroy(pctx.ctx, NULL);
  free(pctx.pmod);

  return 0;
}