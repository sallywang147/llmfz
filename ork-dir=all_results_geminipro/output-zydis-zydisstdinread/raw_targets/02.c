#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string input = stream.ConsumeRemainingBytesAsString();
  const char* input_ptr = input.c_str();
  const size_t input_size = input.size();
  char buf[1024];

  ZydisDecoder decoder;
  ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64,
                   ZYDIS_ADDRESS_WIDTH_64);
  ZydisFormatter formatter;
  ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

  while (ZydisStdinRead(nullptr, buf, sizeof(buf)) != 0) {
    ZydisDecodedInstruction instruction;
    ZydisDecodedOperand operands[ZYDIS_MAX_OPERANDS];
    ZydisDecodedRegister registers[ZYDIS_MAX_REGISTERS];
    ZydisDecodedMemory memory;

    ZydisDecoderDecodeBuffer(&decoder, buf, sizeof(buf), &instruction);

    ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
                                   registers, &memory, buf, sizeof(buf));

    printf("%s\n", buf);
  }

  return 0;
}