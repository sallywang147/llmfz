#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCObjectFileInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string target_triple = stream.ConsumeRandomLengthString();
  const std::string cpu = stream.ConsumeRandomLengthString();
  const std::string features = stream.ConsumeRandomLengthString();
  const std::string reloc_model = stream.ConsumeRandomLengthString();
  const std::string code_model = stream.ConsumeRandomLengthString();
  const std::string asm_dialect = stream.ConsumeRandomLengthString();
  const std::string obj_format = stream.ConsumeRandomLengthString();
  const std::string arch_name = stream.ConsumeRandomLengthString();
  const std::string subtarget = stream.ConsumeRandomLengthString();

  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmPrinters();
  llvm::InitializeAllAsmParsers();

  llvm::TargetRegistry* registry = llvm::TargetRegistry::get();
  llvm::Target* target = registry->findTargetByTriple(target_triple);
  if (!target) {
    return 0;
  }
  llvm::MCSubtargetInfo subtarget_info(target, cpu, features);
  llvm::MCRegisterInfo register_info(target);
  llvm::MCAsmInfo asm_info(target->createMCAsmInfo(arch_name, subtarget, reloc_model,
                                                  code_model, asm_dialect, obj_format));
  llvm::MCObjectFileInfo object_file_info;
  llvm::MCContext context(register_info, asm_info, object_file_info);
  llvm::MCStreamer streamer(context, nullptr, nullptr);
  llvm::MCInstPrinter printer(subtarget_info, register_info, asm_info, *target->createMCInstPrinter(
      asm_dialect, asm_info, subtarget_info, object_file_info, streamer));

  llvm::MCInst inst;
  if (!inst.parse(stream.ConsumeRemainingBytesAsString(), context)) {
    Alpha_printInst(&inst, &streamer.getCommentOS(), nullptr);
  }

  return 0;
}