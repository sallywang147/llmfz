#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZydisDecodedInstruction instruction;
  ZydisDecodedOperand operand;
  ZydisRegisterContext registerContext;
  size_t address;

  // Initialize the structures
  memset(&instruction, 0, sizeof(ZydisDecodedInstruction));
  memset(&operand, 0, sizeof(ZydisDecodedOperand));
  memset(&registerContext, 0, sizeof(ZydisRegisterContext));

  // Consume data for the instruction and operand structures
  if (stream.remaining_bytes() >= sizeof(ZydisDecodedInstruction)) {
    stream.ConsumeData(&instruction, sizeof(ZydisDecodedInstruction));
  } else {
    return 0;
  }

  if (stream.remaining_bytes() >= sizeof(ZydisDecodedOperand)) {
    stream.ConsumeData(&operand, sizeof(ZydisDecodedOperand));
  } else {
    return 0;
  }

  // Consume data for the address and registerContext
  size_t address = stream.ConsumeIntegral<size_t>();
  if (stream.remaining_bytes() >= sizeof(ZydisRegisterContext)) {
    stream.ConsumeData(&registerContext, sizeof(ZydisRegisterContext));
  } else {
    return 0;
  }

  // Call the target function
  ZydisCalcAbsoluteAddressEx(&instruction, &operand, address, &registerContext, &address);

  return 0;
}