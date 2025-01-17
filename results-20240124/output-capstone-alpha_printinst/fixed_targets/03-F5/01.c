#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCParser/MCTargetAsmParser.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/Support/raw_string_ostream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string text = stream.ConsumeRemainingBytesAsString();
  llvm::MCInst inst;
  llvm::MCContext context;
  llvm::MCInstrInfo info;
  llvm::MCRegisterInfo reg_info;
  llvm::MCSubtargetInfo sub_info;
  llvm::MCStreamer streamer(context, nullptr, nullptr);
  llvm::MCObjectStreamer object_streamer(streamer);
  llvm::MCTargetAsmParser parser(object_streamer, context, reg_info, info, sub_info);
  llvm::MCAsmParser asm_parser(parser, context, reg_info, info, sub_info);
  llvm::MCInstPrinter printer(info, reg_info, sub_info, *object_streamer.getCommentOS());
  llvm::raw_string_ostream sstream;
  std::string info_str;
  if (asm_parser.ParseInstruction(text, inst, info_str)) {
    return 0;
  }
  printer.printInst(&inst, sstream, "", info_str);

  // Call the Alpha_printInst function
  extern void Alpha_printInst(const llvm::MCInst* Inst, llvm::raw_ostream& O, const char* Annot);
  Alpha_printInst(&inst, &sstream, info_str.c_str());

  return 0;
}