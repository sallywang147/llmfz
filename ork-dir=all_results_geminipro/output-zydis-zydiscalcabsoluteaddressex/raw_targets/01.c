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
  ZydisDecodedOperand operands[ZYDIS_MAX_OPERANDS];
  size_t operand_count = 0;

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