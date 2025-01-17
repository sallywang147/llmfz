#include <fuzzer/FuzzedDataProvider.h>
#include <llvm/MC/MCInst.h>
#include <llvm/MC/MCStreamer.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCRegisterInfo.h>
#include <llvm/MC/MCInstPrinter.h>
#include <llvm/Support/Sstream.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize MCInst
  llvm::MCInst MI;
  MI.setOpcode(stream.ConsumeIntegral<uint16_t>());
  size_t numOperands = stream.ConsumeIntegralInRange<size_t>(0, 10);
  for (size_t i = 0; i < numOperands; ++i) {
    MI.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<int32_t>()));
  }

  // Initialize SStream
  llvm::SStream O;

  // Initialize Info
  std::string Info = stream.ConsumeRandomLengthString();
  
  Alpha_LLVM_printInstruction(&MI, &O, Info.data());

  return 0;
}