#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"

extern "C" {
#include "llvm/MC/AArch64/AArch64InstPrinter.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string triple = stream.ConsumeRemainingBytesAsString();

  const llvm::Target* target = llvm::TargetRegistry::lookupTarget(triple);
  if (!target) {
    return 0;
  }
  llvm::TargetOptions options;
  std::unique_ptr<llvm::MCSubtargetInfo> subtargetInfo(target->createMCSubtargetInfo(
      triple, "", options));
  llvm::MCInstPrinter printer(nullptr, *subtargetInfo, options.AsmBackend);
  llvm::MCInst inst;
  llvm::SStream streamBuffer;
  AArch64AppleInstPrinter_printInst(&inst, 0, nullptr, &streamBuffer);
  return 0;
}