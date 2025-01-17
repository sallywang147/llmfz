 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t mc_inst_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  uint8_t* mc_inst_data = static_cast<uint8_t*>(malloc(mc_inst_size));
  stream.ConsumeBytes<uint8_t>(mc_inst_data, mc_inst_size);
  llvm::MCInst mc_inst;
  mc_inst.setOpcode(stream.ConsumeIntegral<uint16_t>());
  mc_inst.setDesc(llvm::MCInstDesc{stream.ConsumeIntegral<uint16_t>(),
                                 stream.ConsumeIntegral<uint16_t>(),
                                 stream.ConsumeIntegral<uint16_t>(),
                                 stream.ConsumeIntegral<uint16_t>()});
  mc_inst.addOperand(llvm::MCOperand::createReg(stream.ConsumeIntegral<uint16_t>()));
  mc_inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));
  mc_inst.addOperand(llvm::MCOperand::createReg(stream.ConsumeIntegral<uint16_t>()));
  mc_inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));

  llvm::MCStreamer streamer(llvm::MCSubtargetInfo(), nullptr, nullptr);
  char info[100];
  memset(info, 0, sizeof(info));
  Alpha_LLVM_printInstruction(&mc_inst, &streamer, info);
  free(mc_inst_data);
  return 0;
}