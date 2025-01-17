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

  // Initialize the pctx and ext structures
  memset(&pctx, 0, sizeof(pctx));
  memset(&ext, 0, sizeof(ext));

  // Call the function under test
  int result = yangdata_parse(&pctx, &ext);

  return 0;
}