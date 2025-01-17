#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t arch = stream.ConsumeIntegral<uint8_t>();
  const char* triple = nullptr;
  switch (arch) {
    case 0:
      triple = "aarch64-apple-darwin";
      break;
    case 1:
      triple = "aarch64-linux-gnu";
      break;
    case 2:
      triple = "aarch64-windows";
      break;
    default:
      return 0;
  }

  std::string error;
  const llvm::Target* target =
      llvm::TargetRegistry::lookupTarget(triple, error);
  if (!target) {
    return 0;
  }

  llvm::MCSubtargetInfo STI(target->createMCSubtargetInfo(triple, "", ""));
  llvm::MCRegisterInfo MRI(target->createMCRegInfo(triple));
  llvm::MCInstrInfo MII(target->createMCInstrInfo());
  llvm::MCStreamer OS(llvm::MCStreamer::create(llvm::raw_null_ostream()));
  llvm::SStream Annot;

  const uint8_t opcode = stream.ConsumeIntegral<uint8_t>();
  llvm::MCInst inst;
  if (!MII.parseInstruction(inst, opcode, STI)) {
    return 0;
  }

  AArch64AppleInstPrinter_printInst(&inst, 0, nullptr, &OS);

  return 0;
}