#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include "Zydis/Zydis.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZydisDecoder decoder;
  ZydisDecodedInstruction instruction;
  ZydisRegisterContext register_context;
  ZydisDecodedOperand operands[ZYDIS_MAX_OPERANDS];
  size_t operand_count = 0;

  // Declare the function `ZydisDecoderInit` in the current scope.
  int ZydisDecoderInit(ZydisDecoder* decoder, ZydisMachineMode machine_mode,
                       ZydisAddressWidth address_width);

  // Declare the function `ZydisDecoderDecodeBuffer` in the current scope.
  int ZydisDecoderDecodeBuffer(ZydisDecoder* decoder, const void* buffer,
                              size_t buffer_size, ZydisDecodedInstruction* instruction);

  // Declare the function `ZydisCalcAbsoluteAddressEx` in the current scope.
  int ZydisCalcAbsoluteAddressEx(const ZydisDecodedInstruction* instruction,
                                const ZydisDecodedOperand* operand, size_t operand_index,
                                const ZydisRegisterContext* register_context,
                                ZydisU64* absolute_address);

  ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_ADDRESS_WIDTH_64);

  if (ZydisDecoderDecodeBuffer(&decoder, stream.ConsumeRemainingBytes().data(),
                               stream.remaining_bytes(), &instruction) !=
      ZYAN_STATUS_SUCCESS) {
    return 0;
  }

  for (size_t i = 0; i < instruction.operand_count; i++) {
    ZydisDecodedOperand& operand = operands[i];
    ZydisCalcAbsoluteAddressEx(&instruction, &operand, i, &register_context,
                               &operand.abs_addr);
    operand_count++;
  }

  return 0;
}