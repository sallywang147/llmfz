 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCInstPrinter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string mnemonic = stream.ConsumeRemainingBytesAsString();
  const char* mnemonic_c = mnemonic.c_str();

  llvm::MCContext context;
  llvm::MCObjectStreamer str(context);
  llvm::MCInstPrinter printer(nullptr, str);
  llvm::MCSubtargetInfo STI;
  llvm::MCRegisterInfo RI(STI);
  llvm::MCAsmParser parser(STI, RI);
  llvm::MCInst inst;

  if (parser.parseOneInstruction(mnemonic_c, inst)) {
    return 0;
  }

  Alpha_LLVM_printInstruction(&inst, &str.getCommentOS(), nullptr);

  return 0;
}