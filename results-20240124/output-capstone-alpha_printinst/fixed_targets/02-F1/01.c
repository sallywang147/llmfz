#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>

extern "C" {
#include "AlphaGenMCInstLower.inc"
#include "AlphaGenMCInstLower.h"
#include "AlphaMCInstLower.h"
#include "AlphaRegisterInfo.h"
#include "AlphaSubtarget.h"
}

#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a MCContext.
  llvm::MCContext Ctx;

  // Create a MCRegisterInfo.
  llvm::MCRegisterInfo MRI(llvm::Alpha::createAlphaRegisterInfo(Ctx));

  // Create a MCSubtargetInfo.
  llvm::Triple TT("alpha-unknown-unknown");
  llvm::StringRef CPU = "ev6";
  llvm::StringRef FS = "";
  llvm::TargetMachine TM(TT, CPU, FS);
  const llvm::MCSubtargetInfo* STI = TM.getSubtargetImpl()->getMCSubtargetInfo();

  // Create a MCInstInfo.
  llvm::MCInstInfo MII;

  // Create a MCStreamer.
  llvm::raw_string_ostream OS;
  llvm::MCStreamer Str(OS, 0);

  // Create a MCInst.
  llvm::MCInst MI;

  // Create a SStream.
  llvm::SStream SS;

  // Create a char array for Info.
  char Info[1024];

  // Initialize the MCInst.
  llvm::MCInstLower::Initialize(MII);
  llvm::AlphaGenMCInstLower::Initialize(MII);
  llvm::MCInstLower MCIL(MII, MRI);

  // Fuzz the MCInst.
  for (size_t i = 0; i < size; i++) {
    uint8_t byte = stream.ConsumeIntegral<uint8_t>();
    MCIL.lowerInstruction(byte, MI);
  }

  // Print the MCInst.
  Alpha_printInst(&MI, &SS, Info);

  // Return 0.
  return 0;
}