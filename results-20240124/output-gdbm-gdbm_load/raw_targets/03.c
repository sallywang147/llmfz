 #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fuzzer/FuzzedDataProvider.h>
#include <gdbm.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char* filename = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100)).c_str();
  int replace = stream.ConsumeIntegral<int>();
  int meta_mask = stream.ConsumeIntegral<int>();
  size_t line;
  gdbm_file_info* pdbf;

  gdbm_load(&pdbf, filename, replace, meta_mask, &line);
  gdbm_close(pdbf);
  return 0;
}