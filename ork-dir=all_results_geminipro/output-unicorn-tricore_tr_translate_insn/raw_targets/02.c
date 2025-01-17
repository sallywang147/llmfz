#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tricore_tr_disasm.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  struct DisasContextBase dcbase;
  struct CPUState cpu;

  dcbase.pc = provider.ConsumeIntegral<uint32_t>();
  cpu.pc = dcbase.pc;
  cpu.npc = dcbase.pc;
  cpu.regs[0] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[1] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[2] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[3] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[4] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[5] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[6] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[7] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[8] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[9] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[10] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[11] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[12] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[13] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[14] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[15] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[16] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[17] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[18] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[19] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[20] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[21] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[22] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[23] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[24] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[25] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[26] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[27] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[28] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[29] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[30] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[31] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[32] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[33] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[34] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[35] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[36] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[37] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[38] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[39] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[40] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[41] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[42] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[43] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[44] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[45] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[46] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[47] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[48] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[49] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[50] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[51] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[52] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[53] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[54] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[55] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[56] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[57] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[58] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[59] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[60] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[61] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[62] = provider.ConsumeIntegral<uint32_t>();
  cpu.regs[63] = provider.ConsumeIntegral<uint32_t>();

  tricore_tr_translate_insn(&dcbase, &cpu);

  return 0;
}