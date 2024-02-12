#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCStreamer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  // Create a random MCInst.
  llvm::MCInst inst;
  inst.setOpcode(stream.ConsumeIntegral<uint16_t>());
  inst.addOperand(llvm::MCOperand::createReg(stream.ConsumeIntegral<uint16_t>()));
  inst.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<uint64_t>()));

  // Create a random MCStreamer.
  llvm::raw_string_ostream stream_buffer;
  llvm::MCStreamer streamer(stream_buffer);

  // Print the MCInst to the SStream.
  AArch64AppleInstPrinter_printInst(&inst, 0, nullptr, &stream_buffer);

  // Get the string from the SStream.
  std::string str = stream_buffer.str();

  // Print the string to stdout.
  printf("%s\n", str.c_str());

  return 0;
}