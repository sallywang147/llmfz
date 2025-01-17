#include <fuzzer/FuzzedDataProvider.h>

#include <stdlib.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  TT_SizeRec_ *size = new TT_SizeRec_();
  char pedantic = fdp.ConsumeBool();
  int ret = tt_size_ready_bytecode(size, pedantic);
  delete size;
  return ret;
}