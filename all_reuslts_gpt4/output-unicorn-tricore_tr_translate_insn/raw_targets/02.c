#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "disas/disas.h"
#include "cpu.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the DisasContextBase struct
  DisasContextBase dcbase;
  dcbase.pc_first = stream.ConsumeIntegral<uint64_t>();
  dcbase.pc_next = stream.ConsumeIntegral<uint64_t>();
  dcbase.singlestep_enabled = stream.ConsumeBool();

  // Initialize the CPUState struct
  CPUState cpu;
  cpu.pc = stream.ConsumeIntegral<uint64_t>();

  // Call the function to fuzz
  tricore_tr_translate_insn(&dcbase, &cpu);

  return 0;
}