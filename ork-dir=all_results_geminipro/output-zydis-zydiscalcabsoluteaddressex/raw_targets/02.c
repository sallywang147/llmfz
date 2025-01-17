#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZydisDecoder decoder;
  ZydisDecodedInstruction instruction;
  ZydisRegisterContext register_context;
  size_t offset = 0;

  ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);
  ZydisRegisterContextInit(&register_context);

  while (stream.remaining_bytes() > 0) {
    const size_t instruction_size =
        stream.ConsumeIntegralInRange<size_t>(1, 15);
    std::vector<uint8_t> instruction_bytes =
        stream.ConsumeBytes<uint8_t>(instruction_size);

    ZydisDecodedInstructionClear(&instruction);
    ZydisDecoderDecodeBuffer(&decoder, instruction_bytes.data(),
                             instruction_bytes.size(), &offset, &instruction);

    size_t operand_count = instruction.operand_count;
    if (operand_count > 0) {
      std::vector<ZydisDecodedOperand> operands(operand_count);
      for (size_t i = 0; i < operand_count; ++i) {
        ZydisDecodedOperandClear(&operands[i]);
        ZydisDecoderGetOperandDecodeStatus(&instruction, i, &operands[i]);
      }

      size_t address_size = 0;
      ZydisCalcAbsoluteAddressEx(&instruction, &operands[0], 0,
                                 &register_context, &address_size);
    }
  }

  return 0;
}