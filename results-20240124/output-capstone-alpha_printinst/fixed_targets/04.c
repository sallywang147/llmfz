#include <cstdint>
#include <cstring>
#include <llvm/MC/MCInst.h>
#include <llvm/MC/MCParser/MCAsmParser.h>
#include <llvm/MC/MCStreamer.h>
#include <llvm/MC/MCSubtargetInfo.h>
#include <llvm/MC/MCTargetOptions.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  llvm::FuzzedDataProvider stream(data, size);
  llvm::MCInst inst;
  llvm::MCAsmParser parser(stream.ConsumeRemainingBytesAsString());
  llvm::MCStreamer streamer(llvm::MCSubtargetInfo(), llvm::MCTargetOptions());
  llvm::MCContext context(llvm::Triple(), llvm::MCAsmInfo(), nullptr, nullptr);
  if (!parser.parse(inst, context)) {
    streamer.printInst(&inst, &streamer.getCommentOS(), nullptr);
    Alpha_printInst(&inst, &streamer.getCommentOS(), nullptr); // Call Alpha_printInst here
  }
  return 0;
}