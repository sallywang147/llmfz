 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/SourceMgr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t instruction_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t instruction_bytes[instruction_size];
  stream.ConsumeBytes<uint8_t>(instruction_bytes, instruction_size);
  const uint8_t address = stream.ConsumeIntegral<uint8_t>();
  const std::string annotation = stream.ConsumeRemainingBytesAsString();
  const char* annotation_c_str = annotation.c_str();
  struct MCInst instruction;
  instruction.setOpcode(0);
  instruction.addOperand(MCOperand::createImm(0));
  struct MCInstPrinter printer(nullptr, nullptr);
  struct MCStreamer streamer(nullptr, nullptr);
  struct MCSubtargetInfo subtarget_info;
  struct SStream stream_buffer;
  printer.printInst(&instruction, address, annotation_c_str, &stream_buffer);
  return 0;
}