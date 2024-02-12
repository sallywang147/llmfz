 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string filename = stream.ConsumeRemainingBytesAsString();
  struct gdbm_file_info* pdbf = nullptr;
  size_t line = 0;
  gdbm_load(&pdbf, const_cast<char*>(filename.c_str()), stream.ConsumeBool(),
             stream.ConsumeIntegral<int>(), &line);
  gdbm_close(pdbf);
  return 0;
}