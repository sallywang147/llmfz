 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "gdbm.h"
#include "gdbm_internal.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t line_size = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> line_buffer(line_size);
  provider.ConsumeBytes<char>(line_buffer.data(), line_size);
  line_buffer.push_back('\n');
  FILE* fp = fmemopen(line_buffer.data(), line_buffer.size(), "r");
  struct gdbm_file_info* pdbf = nullptr;
  size_t line = 0;
  gdbm_load_from_file(&pdbf, fp, 0, 0, &line);
  fclose(fp);
  return 0;
}