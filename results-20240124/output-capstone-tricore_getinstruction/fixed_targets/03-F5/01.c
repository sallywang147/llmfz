#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include <capstone/capstone.h>
#include <capstone/tricore.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t handle = stream.ConsumeIntegral<size_t>();
  const size_t byte_len = stream.ConsumeIntegral<size_t>();
  const size_t address = stream.ConsumeIntegral<size_t>();
  std::vector<char> bytes = stream.ConsumeBytes<char>(byte_len);
  csh handle;
  cs_insn* insn;
  size_t count;
  if (cs_open(CS_ARCH_TRICORE, CS_MODE_LITTLE_ENDIAN, &handle) != CS_ERR_OK) {
    return 0;
  }
  count = cs_disasm(handle, bytes.data(), byte_len, address, 0, &insn);
  if (count > 0) {
    cs_free(insn, count);
  }
  cs_close(&handle);
  return 0;
}