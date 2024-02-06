#include <fuzzer/FuzzedDataProvider.h>
#include <llvm/MC/MCInst.h>
#include <llvm/MC/MCInstPrinter.h>
#include <llvm/MC/MCStreamer.h>
#include <llvm/MC/MCSubtargetInfo.h>
#include <llvm/Support/raw_ostream.h>

extern "C" {
#include <Alpha/Alpha_LLVM_printInstruction.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  FuzzedDataProvider DataProvider(Data, Size);
  llvm::MCInst Inst;
  llvm::MCInstPrinter Printer;
  llvm::SStream Out;
  llvm::MCSubtargetInfo STI;
  Printer.setPrintImmHex(true);
  Printer.setPrintBranchImmAsHex(true);
  while (DataProvider.remaining_bytes() > 0) {
    Inst.clear();
    if (DataProvider.ConsumeBool())
      Inst.setOpcode(DataProvider.ConsumeIntegral<llvm::unsigned>());
    else
      Inst.setOpcode(llvm::MCInst::PHI);
    uint64_t NumOperands = DataProvider.ConsumeIntegral<uint64_t>();
    for (uint64_t i = 0; i < NumOperands; i++) {
      if (DataProvider.ConsumeBool())
        Inst.addOperand(llvm::MCOperand::createImm(
            DataProvider.ConsumeIntegral<uint64_t>()));
      else if (DataProvider.ConsumeBool())
        Inst.addOperand(llvm::MCOperand::createReg(
            DataProvider.ConsumeIntegral<uint64_t>()));
      else if (DataProvider.ConsumeBool())
        Inst.addOperand(llvm::MCOperand::createFPImm(
            llvm::APFloat(DataProvider.ConsumeFloatingPoint<double>())));
    }
    Alpha_LLVM_printInstruction(&Inst, &Out, "");
    Out.flush();
  }
  return 0;
}