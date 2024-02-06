#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <Zydis/Zydis.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ZydisDecodedInstruction instruction;
  ZydisDecodedOperand operand;
  ZydisRegisterContext context;
  size_t result;

  // Initialize the structures to zero
  memset(&instruction, 0, sizeof(ZydisDecodedInstruction));
  memset(&operand, 0, sizeof(ZydisDecodedOperand));
  memset(&context, 0, sizeof(ZydisRegisterContext));

  // Consume data for the structures
  stream.ConsumeData(&instruction, sizeof(ZydisDecodedInstruction));
  stream.ConsumeData(&operand, sizeof(ZydisDecodedOperand));
  stream.ConsumeData(&context, sizeof(ZydisRegisterContext));

  // Consume data for the displacement
  size_t displacement = stream.ConsumeIntegral<size_t>();

  // Call the function under test
  int status = ZydisCalcAbsoluteAddressEx(&instruction, &operand, displacement, &context, &result);

  return 0;
}