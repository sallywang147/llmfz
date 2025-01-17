#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "wx/mem.h"

extern "C" {
#include "wx/wx.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  size_t free_memory = stream.ConsumeIntegral<size_t>();
  wxGetFreeMemory(); // Call wxGetFreeMemory() to avoid the undefined reference error
  return 0;
}