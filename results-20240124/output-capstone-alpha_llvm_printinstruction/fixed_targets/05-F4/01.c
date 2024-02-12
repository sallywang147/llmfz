#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/raw_ostream.h"

extern "C" {
  void Alpha_LLVM_printInstruction(struct MCInst * MI, struct SStream * O, char * Info);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, 100));
  llvm::MCInst inst;
  inst.setOpcode(stream.ConsumeIntegral<uint16_t>());
  inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));
  inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));
  inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));
  llvm::MCSubtargetInfo STI;
  llvm::raw_string_ostream OS;
  llvm::raw_ostream& S = OS;
  Alpha_LLVM_printInstruction(&inst, (struct SStream *)&S, nullptr);
  return 0;
}