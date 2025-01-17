#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct IterCellsResolution itR;
  itR.lat = stream.ConsumeIntegral<int64_t>();
  itR.lon = stream.ConsumeIntegral<int64_t>();
  itR.res = stream.ConsumeIntegral<int>();
  itR.cell_count = stream.ConsumeIntegral<int64_t>();
  itR.cells = new int64_t[itR.cell_count];
  for (int64_t i = 0; i < itR.cell_count; i++) {
    itR.cells[i] = stream.ConsumeIntegral<int64_t>();
  }
  iterStepRes(&itR);
  delete[] itR.cells;
  return 0;
}