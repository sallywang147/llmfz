#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstPrinter.h"
#include "llvm/MC/MCParser/MCAsmParser.h"
#include "llvm/MC/MCParser/MCParsedAsmOperand.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCObjectStreamer.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

#include "AArch64AppleInstPrinter.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a target machine.
  const char* triple = "aarch64-apple-ios";
  llvm::Target* target = llvm::TargetRegistry::lookupTarget(triple);
  llvm::TargetOptions options;
  llvm::TargetMachine* target_machine =
      target->createTargetMachine(triple, "generic", options);

  // Create a context.
  llvm::MCContext context;

  // Create an assembler info.
  llvm::MCAsmInfo* asm_info = target_machine->createMCAsmInfo(triple);

  // Create a register info.
  llvm::MCRegisterInfo* register_info = target_machine->createMCRegInfo(triple);

  // Create an instruction info.
  llvm::MCInstrInfo* instruction_info = target_machine->createMCInstrInfo();

  // Create a disassembler.
  llvm::MCDisassembler* disassembler = target_machine->createMCDisassembler();

  // Create an instruction printer.
  llvm::AArch64AppleInstPrinter* instruction_printer =
      new llvm::AArch64AppleInstPrinter(asm_info, register_info,
                                        *disassembler);

  // Create a stream writer.
  llvm::raw_svector_ostream stream_writer;

  // Create a streamer.
  llvm::MCStreamer* streamer = target_machine->createMCObjectStreamer(
      triple, context, stream_writer, asm_info);

  // Create an assembler parser.
  llvm::MCAsmParser* assembler_parser = target_machine->createMCAsmParser(
      context, *streamer, *asm_info, register_info);

  // Create a source manager.
  llvm::SourceMgr source_manager;

  // Create a memory buffer.
  std::string assembly_string = stream.ConsumeRemainingBytesAsString();
  llvm::MemoryBuffer* memory_buffer =
      llvm::MemoryBuffer::getMemBufferCopy(assembly_string);

  // Add the memory buffer to the source manager.
  source_manager.AddNewSourceBuffer(memory_buffer, llvm::SMLoc());

  // Create an assembly parser.
  llvm::MCAsmParser* assembly_parser =
      target_machine->createMCAsmParser(context, *streamer, *asm_info,
                                         register_info);

  // Parse the assembly.
  llvm::MCAsmParser::ParseResult parse_result =
      assembly_parser->parse(source_manager, assembler_parser);

  // Check if the assembly parsed successfully.
  if (parse_result != llvm::MCAsmParser::ParseResult::Success) {
    return 0;
  }

  // Get the instruction.
  llvm::MCInst* instruction = streamer->getInstruction();

  // Print the instruction.
  AArch64AppleInstPrinter_printInst(instruction, 0, nullptr, streamer);

  // Delete the instruction printer.
  delete instruction_printer;

  // Delete the streamer.
  delete streamer;

  // Delete the assembler parser.
  delete assembly_parser;

  // Delete the memory buffer.
  delete memory_buffer;

  // Delete the target machine.
  delete target_machine;

  return 0;
}