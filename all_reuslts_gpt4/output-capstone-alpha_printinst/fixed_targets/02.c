#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include "MCInst.h"
#include "SStream.h"

extern void Alpha_printInst(struct MCInst * MI, struct SStream * O, char * Info);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize MCInst
  struct MCInst MI;
  MI.opcode = stream.ConsumeIntegral<uint16_t>();
  MI.operandsNum = stream.ConsumeIntegralInRange<uint8_t>(0, MCINST_MAX_OPERANDS);
  for (int i = 0; i < MI.operandsNum; ++i) {
    MI.operands[i].type = (MCOperandType)stream.ConsumeIntegralInRange<uint8_t>(0, 1);
    if (MI.operands[i].type == kOperandType_Register) {
      MI.operands[i].reg = stream.ConsumeIntegral<uint16_t>();
    } else {
      MI.operands[i].imm = stream.ConsumeIntegral<int32_t>();
    }
  }

  // Initialize SStream
  struct SStream O;
  O.index = stream.ConsumeIntegralInRange<uint64_t>(0, SSTREAM_MAX_SIZE - 1);
  O.buffer[O.index] = '\0';  // Ensure it's null-terminated

  // Initialize Info
  std::string Info = stream.ConsumeRemainingBytesAsString();
  
  Alpha_printInst(&MI, &O, const_cast<char*>(Info.c_str()));

  return 0;
}