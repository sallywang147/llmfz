 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "MCInst.h"
#include "MCSubtargetInfo.h"
#include "SStream.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t opcode = stream.ConsumeIntegral<uint8_t>();
  const uint8_t operand_count = stream.ConsumeIntegral<uint8_t>();
  const uint8_t operands[operand_count];
  for (uint8_t i = 0; i < operand_count; i++) {
    operands[i] = stream.ConsumeIntegral<uint8_t>();
  }
  const std::string info = stream.ConsumeRemainingBytesAsString();

  MCInst inst;
  inst.setOpcode(opcode);
  for (uint8_t i = 0; i < operand_count; i++) {
    inst.addOperand(MCOperand::createImm(operands[i]));
  }

  struct SStream stream_obj;
  SStream_Init(&stream_obj);
  Alpha_LLVM_printInstruction(&inst, &stream_obj, const_cast<char*>(info.c_str()));
  SStream_Done(&stream_obj);

  return 0;
}