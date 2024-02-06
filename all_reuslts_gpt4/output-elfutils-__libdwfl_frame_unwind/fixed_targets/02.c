#include "system.h"
#include <assert.h>
#include <fcntl.h>
#include <gelf.h>
#include <inttypes.h>
#include <libdwfl.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <fuzzer/FuzzedDataProvider.h>

void fuzz_logic(char *filename) {
  (void)elf_version(EV_CURRENT);
  int fd = open(filename, O_RDONLY);
  Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
  if (elf != NULL) {
    Dwfl *dwfl = dwfl_begin(NULL);
    if (dwfl != NULL) {
      Dwfl_Module *mod = dwfl_report_elf(dwfl, "fuzz", filename, fd, 0);
      if (mod != NULL) {
        Dwarf_Addr bias;
        Dwarf_CFI *cfi = dwfl_module_eh_cfi(mod, &bias);
        if (cfi != NULL) {
          Dwarf_Addr pc = 0;
          Dwarf_Frame *frame = dwarf_cfi_addrframe(cfi, pc);
          if (frame != NULL) {
            Dwfl_Frame *state = (Dwfl_Frame *)malloc(sizeof(Dwfl_Frame));
            state->pc_state = frame;
            __libdwfl_frame_unwind(state);
            free(state);
          }
        }
        dwfl_report_end(dwfl, NULL, NULL);
      }
      dwfl_end(dwfl);
    }
    elf_end(elf);
  }
  close(fd);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char filename[] = "/tmp/fuzz-libdwfl.XXXXXX";
  int fd;
  ssize_t n;

  fd = mkstemp(filename);
  assert(fd >= 0);

  n = write(fd, data, size);
  assert(n == (ssize_t)size);

  close(fd);

  fuzz_logic(filename);

  unlink(filename);
  return 0;
}