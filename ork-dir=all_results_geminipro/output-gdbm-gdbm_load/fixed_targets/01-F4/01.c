#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gdbm.h>

extern "C" {
#include <gdbm-ndbm.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  int replace = stream.ConsumeBool();
  int meta_mask = stream.ConsumeIntegral<int>();
  size_t line;
  struct gdbm_file_info* pdbf;
  int ret = gdbm_load(&pdbf, filename.c_str(), replace, meta_mask, &line);
  if (ret == 0) {
    gdbm_close(pdbf);
  }
  return 0;
}