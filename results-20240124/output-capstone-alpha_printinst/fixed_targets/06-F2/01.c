#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include <llvm/MC/MCInst.h>
#include <llvm/MC/MCInstPrinter.h>
#include <llvm/MC/MCStreamer.h>
#include <llvm/MC/MCSubtargetInfo.h>
#include <llvm/MC/MCObjectStreamer.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCRegisterInfo.h>
#include <llvm/MC/MCDisassembler/MCDisassembler.h>
#include <llvm/MC/MCDisassembler/MCFixedLenDisassembler.h>
#include <llvm/MC/MCDisassembler/MCInstPrinter.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  using namespace llvm;

  LLVMContext Context;
  MCRegisterInfo MRI(Triple("alpha"));
  MCSubtargetInfo STI(Triple("alpha"), "", "");
  MCObjectStreamer OS(Context, STI);
  MCInstPrinter Printer(OS, STI);

  std::vector<uint8_t> Instructions(data, data + size);
  MCDisassembler* Disassembler = createAlphaDisassembler();
  if (!Disassembler) {
    return 0;
  }

  MCInst Inst;
  SStream SS;
  while (Disassembler->getInstruction(Instructions.data(), Instructions.size(),
                                     Inst, SS, STI)) {
    Alpha_printInst(&Inst, &SS, nullptr);
  }

  delete Disassembler;
  return 0;
}