#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "AlphaGenMCAsmWriter.h"
#include "AlphaMCInst.h"
#include "AlphaMCInstrInfo.h"
#include "AlphaMCTargetDesc.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCParser/MCAsmParserExtension.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetParser.h"

using namespace llvm;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string assembly_string = stream.ConsumeRemainingBytesAsString();

  std::string error;
  const Target *target = TargetRegistry::lookupTarget("alpha", error);
  if (!target) {
    return 0;
  }

  std::unique_ptr<MCRegisterInfo> MRI(target->createMCRegInfo(error));
  if (!MRI) {
    return 0;
  }

  std::unique_ptr<MCInstrInfo> MII(target->createMCInstrInfo());
  if (!MII) {
    return 0;
  }

  std::unique_ptr<MCSubtargetInfo> STI(target->createMCSubtargetInfo(
      Triple(), "", ""));
  if (!STI) {
    return 0;
  }

  std::unique_ptr<MCAsmInfo> MAI(target->createMCAsmInfo(*STI));
  if (!MAI) {
    return 0;
  }

  std::unique_ptr<MCContext> context(new MCContext());
  std::unique_ptr<MCStreamer> streamer(new MCObjectStreamer(*context,
                                                           *MAI));
  MCInstPrinter printer(*MAI, *STI, *context);

  std::unique_ptr<MCAsmParser> parser(createMCAsmParser(
      *STI, *MAI, *context, *streamer, *MRI));
  if (!parser) {
    return 0;
  }

  std::unique_ptr<MCAsmParserExtension> extension(
      target->createMCAsmParserExtension(*STI));
  if (extension) {
    parser->addExtension(std::move(extension));
  }

  if (!parser->parse(assembly_string, &STI->getFeatureBits())) {
    return 0;
  }

  for (const MCInst &inst : parser->getInstructions()) {
    Alpha_LLVM_printInstruction(const_cast<MCInst*>(&inst), nullptr, nullptr);
  }

  return 0;
}