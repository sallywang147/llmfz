 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t max_line_size = provider.ConsumeIntegralInRange<size_t>(1, 1000);
  const int replace = provider.ConsumeBool();
  const int meta_mask = provider.ConsumeIntegral<int>();

  FILE* fp = tmpfile();
  if (fp == nullptr) {
    return 0;
  }
  std::vector<uint8_t> output_buffer(max_line_size + 1);
  while (provider.remaining_bytes() > 0) {
    const size_t next_size = provider.ConsumeIntegralInRange<size_t>(
        0,
        std::min(provider.remaining_bytes(), max_line_size));
    auto next_input = provider.ConsumeBytes<unsigned char>(next_size);
    fwrite(next_input.data(), 1, next_input.size(), fp);
    fputc('\n', fp);
  }
  fseek(fp, 0, SEEK_SET);

  struct gdbm_file_info* pdbf;
  size_t line = 0;
  int ret = gdbm_load_from_file(&pdbf, fp, replace, meta_mask, &line);
  if (ret == 0) {
    gdbm_close(pdbf);
  }
  fclose(fp);

  return 0;
}