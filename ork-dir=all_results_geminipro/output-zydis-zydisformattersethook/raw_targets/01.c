#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const ZydisFormatterStyle style =
      stream.ConsumeBool() ? ZydisFormatterStyle_Intel : ZydisFormatterStyle_Att;
  const ZydisFormatterWidth width =
      stream.PickValueInArray({ZydisFormatterWidth_32Bit, ZydisFormatterWidth_64Bit});
  const std::string text = stream.ConsumeRemainingBytesAsString();

  ZydisFormatter formatter;
  ZydisFormatterInit(&formatter, style, width);

  std::vector<char> output_buffer(text.size() * 2);
  ZydisFormatterSetHook(&formatter, ZydisFormatterHook_PrintMnemonic,
                       &output_buffer[0]);
  ZydisFormatterFormatInstruction(&formatter, reinterpret_cast<const uint8_t*>(text.c_str()),
                               text.size(), &output_buffer[0], output_buffer.size());
  return 0;
}