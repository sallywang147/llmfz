#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/raw_ostream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  llvm::SmallVector<uint8_t, 100> mc_inst_data;
  mc_inst_data.resize(size);
  memcpy(mc_inst_data.data(), data, size);
  llvm::MCInst mc_inst;
  mc_inst.setOpcode(stream.ConsumeIntegral<uint16_t>());
  mc_inst.setDesc(llvm::MCInstDesc(stream.ConsumeIntegral<uint16_t>(),
                   stream.ConsumeIntegral<uint16_t>(),
                   stream.ConsumeIntegral<uint16_t>(),
                   stream.ConsumeIntegral<uint16_t>()));
  mc_inst.addOperand(llvm::MCOperand::createReg(stream.ConsumeIntegral<uint16_t>()));
  mc_inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));
  mc_inst.addOperand(llvm::MCOperand::createReg(stream.ConsumeIntegral<uint16_t>()));
  mc_inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));

  llvm::raw_string_ostream streamer(nullptr);
  char info[100];
  memset(info, 0, sizeof(info));
  Alpha_LLVM_printInstruction(&mc_inst, &streamer, info);
  return 0;
}