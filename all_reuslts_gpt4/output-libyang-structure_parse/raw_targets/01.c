#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libyang.h"
#include "tree_schema.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct lysp_ctx pctx;
  struct lysp_ext_instance ext;
  FuzzedDataProvider stream(data, size);

  // Initialize the lysp_ctx structure
  pctx.ctx = ly_ctx_new(NULL, 0);
  pctx.pmod = lysp_module_new();
  pctx.line = stream.ConsumeIntegral<uint32_t>();
  pctx.indent = stream.ConsumeIntegral<uint16_t>();
  pctx.type = stream.ConsumeIntegral<uint8_t>();
  pctx.parsing = stream.ConsumeIntegral<uint8_t>();
  pctx.status = stream.ConsumeIntegral<uint8_t>();
  pctx.flags = stream.ConsumeIntegral<uint8_t>();
  pctx.format = stream.ConsumeIntegral<uint8_t>();
  pctx.path_len = stream.ConsumeIntegral<uint16_t>();
  pctx.path_pos = stream.ConsumeIntegral<uint16_t>();
  pctx.path = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  pctx.in = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  pctx.in_end = pctx.in + strlen(pctx.in);
  pctx.input_end = pctx.in_end;

  // Initialize the lysp_ext_instance structure
  ext.parent = NULL;
  ext.name = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  ext.argument = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  ext.insubstmt = stream.ConsumeIntegral<uint16_t>();
  ext.insubstmt_index = stream.ConsumeIntegral<uint8_t>();
  ext.parent_stmt = stream.ConsumeIntegral<uint16_t>();
  ext.parent_stmt_index = stream.ConsumeIntegral<uint8_t>();
  ext.format = stream.ConsumeIntegral<uint8_t>();
  ext.flags = stream.ConsumeIntegral<uint8_t>();
  ext.dsc = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  ext.ref = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
  ext.iffeatures = NULL;
  ext.exts = NULL;

  // Call the target function
  int ret = structure_parse(&pctx, &ext);

  // Cleanup
  lysp_module_free(pctx.pmod);
  ly_ctx_destroy(pctx.ctx, NULL);

  return 0;
}