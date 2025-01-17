#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/raw_ostream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t inst_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  uint8_t* inst_bytes = new uint8_t[inst_size];
  stream.ConsumeBytes<uint8_t>(inst_bytes, inst_size);

  llvm::MCInst inst;
  inst.setOpcode(stream.ConsumeIntegral<uint16_t>());
  inst.addOperand(llvm::MCOperand::createReg(stream.ConsumeIntegral<uint16_t>()));
  inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));

  llvm::raw_svector_ostream stream_out(llvm::StringRef());
  llvm::RISCV_printInst(&inst, &stream_out, nullptr);
  delete[] inst_bytes;
  return 0;
}