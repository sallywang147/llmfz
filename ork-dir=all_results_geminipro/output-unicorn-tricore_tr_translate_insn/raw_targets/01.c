#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct DisasContextBase dcbase;
  struct CPUState cpu;

  FuzzedDataProvider provider(data, size);

  // Initialize dcbase
  dcbase.pc = provider.ConsumeIntegral<uint32_t>();
  dcbase.npc = provider.ConsumeIntegral<uint32_t>();
  dcbase.mode = provider.ConsumeIntegral<uint32_t>();
  dcbase.flags = provider.ConsumeIntegral<uint32_t>();
  dcbase.branch_delay = provider.ConsumeIntegral<uint32_t>();
  dcbase.branch_taken = provider.ConsumeBool();
  dcbase.branch_target = provider.ConsumeIntegral<uint32_t>();
  dcbase.branch_type = provider.ConsumeIntegral<uint32_t>();
  dcbase.delay_slot = provider.ConsumeBool();
  dcbase.delay_slot_pc = provider.ConsumeIntegral<uint32_t>();
  dcbase.delay_slot_npc = provider.ConsumeIntegral<uint32_t>();
  dcbase.delay_slot_mode = provider.ConsumeIntegral<uint32_t>();
  dcbase.delay_slot_flags = provider.ConsumeIntegral<uint32_t>();
  dcbase.delay_slot_branch_delay = provider.ConsumeIntegral<uint32_t>();
  dcbase.delay_slot_branch_taken = provider.ConsumeBool();
  dcbase.delay_slot_branch_target = provider.ConsumeIntegral<uint32_t>();
  dcbase.delay_slot_branch_type = provider.ConsumeIntegral<uint32_t>();

  // Initialize cpu
  cpu.env.regs[0] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[1] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[2] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[3] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[4] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[5] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[6] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[7] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[8] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[9] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[10] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[11] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[12] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[13] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[14] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[15] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[16] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[17] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[18] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[19] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[20] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[21] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[22] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[23] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[24] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[25] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[26] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[27] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[28] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[29] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[30] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[31] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[32] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[33] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[34] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[35] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[36] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[37] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[38] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[39] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[40] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[41] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[42] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[43] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[44] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[45] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[46] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[47] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[48] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[49] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[50] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[51] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[52] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[53] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[54] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[55] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[56] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[57] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[58] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[59] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[60] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[61] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[62] = provider.ConsumeIntegral<uint32_t>();
  cpu.env.regs[63] = provider.ConsumeIntegral<uint32_t>();

  // Call the function under test
  tricore_tr_translate_insn(&dcbase, &cpu);

  return 0;
}