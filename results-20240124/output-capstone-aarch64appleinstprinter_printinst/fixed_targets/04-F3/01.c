#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/SourceMgr.h"

extern "C" {
void AArch64AppleInstPrinter_printInst(struct MCInst * MI, size_t Address, char * Annot, struct SStream * O);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t instruction_size = stream.ConsumeIntegral<uint8_t>();
  std::vector<uint8_t> instruction_bytes = stream.ConsumeBytes<uint8_t>(instruction_size);
  const uint8_t address = stream.ConsumeIntegral<uint8_t>();
  const std::string annotation = stream.ConsumeRemainingBytesAsString();
  const char* annotation_c_str = annotation.c_str();
  MCInst instruction;
  instruction.setOpcode(0);
  instruction.addOperand(llvm::MCOperand::createImm(0));
  MCInstPrinter printer(nullptr, nullptr);
  MCStreamer streamer(nullptr, nullptr);
  MCSubtargetInfo subtarget_info;
  SStream stream_buffer;
  AArch64AppleInstPrinter_printInst(&instruction, address, (char*)annotation_c_str, &stream_buffer);
  return 0;
}