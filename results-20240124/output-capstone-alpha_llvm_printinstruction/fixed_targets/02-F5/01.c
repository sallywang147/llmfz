#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/MemoryBuffer.h"
#include "Alpha/AlphaInstPrinter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string target_triple = stream.ConsumeRandomLengthString();
  const std::string asm_string = stream.ConsumeRemainingBytesAsString();
  const llvm::StringRef asm_ref(asm_string);

  std::string error;
  const llvm::Target *target = llvm::TargetRegistry::lookupTarget(target_triple, error);
  if (!target) {
    return 0;
  }

  llvm::MCSubtargetInfo STI;
  llvm::MCRegisterInfo MRI(*target, STI);
  llvm::MCAsmInfo MAI;
  llvm::MCInstrInfo MII(*target, MRI);
  llvm::MCContext MC(MRI);
  llvm::MCStreamer *S = new llvm::MCObjectStreamer();
  llvm::MCInstPrinter IP(MAI, MRI, *S);
  llvm::MCAsmParser Parser(MC, MAI, *S, *target);

  llvm::MemoryBufferRef buffer(asm_ref);
  llvm::SourceMgr SM;
  SM.AddNewSourceBuffer(buffer, llvm::SMLoc());
  Parser.parseAssemblyString(buffer, nullptr);
  for (llvm::MCInst& MI : *S) {
    Alpha_LLVM_printInstruction(&MI, nullptr, nullptr);
  }

  delete S;
  return 0;
}