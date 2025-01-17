#include <fuzzer/FuzzedDataProvider.h>

#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include <capstone/capstone.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  csh handle;
  cs_err err;

  if (Size < 1) {
    // 1 byte for arch choice
    return 0;
  } else if (Size > 0x1000) {
    // limit input to 4kb
    Size = 0x1000;
  }

  err = cs_open(CS_ARCH_ALPHA, CS_MODE_BIG_ENDIAN, &handle);
  if (err) {
    return 0;
  }

  struct cs_struct ud;
  ALPHA_global_init(&ud);

  cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
  if (Data[0] & 0x80) {
    // hack
    cs_option(handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_ATT);
  }

  uint64_t address = 0x1000;
  size_t count = cs_disasm(handle, Data + 1, Size - 1, address, 0, &ud.insn);

  if (count) {
    size_t j;
    unsigned int n;

    for (j = 0; j < count; j++) {
      cs_insn *i = &(ud.insn[j]);
      fprintf(stderr, "0x%" PRIx64 ":\t%s\t\t%s // insn-ID: %u, insn-mnem: %s\n", i->address, i->mnemonic, i->op_str, i->id, cs_insn_name(handle, i->id));

      ud.detail = i->detail;

      if (ud.detail->regs_read_count > 0) {
        fprintf(stderr, "\tImplicit registers read: ");
        for (n = 0; n < ud.detail->regs_read_count; n++) {
          fprintf(stderr, "%s ", cs_reg_name(handle, ud.detail->regs_read[n]));
        }
      }

      if (ud.detail->regs_write_count > 0) {
        fprintf(stderr, "\tImplicit registers modified: ");
        for (n = 0; n < ud.detail->regs_write_count; n++) {
          fprintf(stderr, "%s ", cs_reg_name(handle, ud.detail->regs_write[n]));
        }
      }

      if (ud.detail->groups_count > 0) {
        fprintf(stderr, "\tThis instruction belongs to groups: ");
        for (n = 0; n < ud.detail->groups_count; n++) {
          fprintf(stderr, "%s ", cs_group_name(handle, ud.detail->groups[n]));
        }
      }
    }

    fprintf(stderr, "0x%" PRIx64 ":\n", ud.insn[j - 1].address + ud.insn[j - 1].size);
    cs_free(ud.insn, count);
  }

  cs_close(&handle);

  return 0;
}