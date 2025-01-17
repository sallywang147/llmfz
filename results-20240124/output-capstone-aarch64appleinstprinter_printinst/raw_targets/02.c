 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "AArch64InstPrinter.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/ErrorHandling.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string arch_name = stream.ConsumeRemainingBytesAsString();
  const llvm::Target* target = llvm::TargetRegistry::lookupTarget(arch_name, true);
  if (!target) {
    return 0;
  }
  std::unique_ptr<llvm::MCRegisterInfo> mri(target->createMCRegInfo(arch_name));
  std::unique_ptr<llvm::MCAsmInfo> asm_info(target->createMCAsmInfo(arch_name, "", ""));
  std::unique_ptr<llvm::MCSubtargetInfo> subtarget_info(target->createMCSubtargetInfo(arch_name, "", ""));
  std::unique_ptr<llvm::MCInstrInfo> mcii(target->createMCInstrInfo());
  std::unique_ptr<llvm::MCInstPrinter> inst_printer(target->createMCInstPrinter(
      llvm::Triple(arch_name), asm_info.get(), mri.get(), subtarget_info.get(),
      llvm::MCInstPrinter::PrintStat::AllStats));
  std::unique_ptr<llvm::MCObjectStreamer> streamer(target->createMCObjectStreamer(
      llvm::Triple(arch_name), asm_info.get(), std::make_unique<llvm::MCObjectFileInfo>(),
      std::make_unique<llvm::MCCodeEmitter>(), std::make_unique<llvm::raw_ostream>(),
      std::make_unique<llvm::MCContext>(mri.get()), std::make_unique<llvm::MCAsmBackend>(),
      std::make_unique<llvm::MCObjectWriter>(std::unique_ptr<llvm::MCObjectWriter>(nullptr)),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<llvm::MCSection>(), std::make_unique<llvm::MCSection>(),
      std::make_unique<