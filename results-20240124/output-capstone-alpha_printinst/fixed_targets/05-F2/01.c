#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_os_ostream.h"

using namespace llvm;

extern "C" {
void Alpha_printInst(MCInst *MI, SStream *O, char *Info);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const char* triple = provider.ConsumeRandomLengthString().c_str();
  std::string error;
  const Target *target = TargetRegistry::lookupTarget(triple, error);
  if (!target) {
    return 0;
  }
  std::unique_ptr<MCSubtargetInfo> STI(target->createMCSubtargetInfo(triple, "", ""));
  std::unique_ptr<MCRegisterInfo> MRI(target->createMCRegInfo(triple));
  std::unique_ptr<MCObjectFileInfo> MOFI(new MCObjectFileInfo());
  MCContext context(MRI.get(), MOFI.get(), nullptr);
  MCStreamer streamer(context, nullptr, nullptr, nullptr);
  MCInstPrinter printer(triple, 0, *STI, *MRI, streamer);
  const unsigned opcode = provider.ConsumeIntegral<unsigned>();
  const MCInstrDesc& desc = target->getInstrDesc(opcode);
  std::vector<uint64_t> operands;
  for (unsigned i = 0; i < desc.getNumOperands(); i++) {
    operands.push_back(provider.ConsumeIntegral<uint64_t>());
  }
  MCInst inst;
  inst.setOpcode(opcode);
  for (unsigned i = 0; i < operands.size(); i++) {
    inst.addOperand(MCOperand::createReg(operands[i]));
  }
  Alpha_printInst(&inst, nullptr, nullptr);
  return 0;
}