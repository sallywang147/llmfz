#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "planner.h"
#include "scanner.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct planner_s ego;
  struct scanner_s sc;

  ego.n_files = stream.ConsumeIntegral<uint32_t>();
  ego.max_files = stream.ConsumeIntegral<uint32_t>();
  ego.files = (struct file_s*)malloc(ego.max_files * sizeof(struct file_s));
  for (unsigned int i = 0; i < ego.n_files; i++) {
    ego.files[i].name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100));
    ego.files[i].size = stream.ConsumeIntegral<uint32_t>();
  }

  sc.n_files = stream.ConsumeIntegral<uint32_t>();
  sc.max_files = stream.ConsumeIntegral<uint32_t>();
  sc.files = (struct file_s*)malloc(sc.max_files * sizeof(struct file_s));
  for (unsigned int i = 0; i < sc.n_files; i++) {
    sc.files[i].name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange<size_t>(0, 100));
    sc.files[i].size = stream.ConsumeIntegral<uint32_t>();
  }

  imprt(&ego, &sc);

  free(ego.files);
  free(sc.files);

  return 0;
}