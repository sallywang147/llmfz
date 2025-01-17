#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libyang.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct lysp_ctx pctx;
  struct lysp_ext_instance ext;

  // Initialize the structures with zeros
  memset(&pctx, 0, sizeof(pctx));
  memset(&ext, 0, sizeof(ext));

  // Fill the structures with fuzzing data
  pctx.line = stream.ConsumeIntegral<uint32_t>();
  pctx.size = stream.ConsumeIntegral<size_t>();
  pctx.format = stream.ConsumeEnum<LYS_INFORMAT>();
  pctx.status = stream.ConsumeEnum<LYS_STATUS>();

  ext.name = stream.ConsumeRandomLengthString().c_str();
  ext.argument = stream.ConsumeRandomLengthString().c_str();
  ext.parent_stmt = stream.ConsumeEnum<LY_STMT>();
  ext.parent_stmt_index = stream.ConsumeIntegral<uint8_t>();
  ext.insubstmt = stream.ConsumeEnum<LY_STMT>();
  ext.insubstmt_index = stream.ConsumeIntegral<uint8_t>();
  ext.module = nullptr; // We set it to nullptr to avoid memory issues

  // Call the target function
  int ret = structure_aug_parse(&pctx, &ext);

  return 0;
}