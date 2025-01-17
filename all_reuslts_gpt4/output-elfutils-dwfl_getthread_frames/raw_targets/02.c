#include "system.h"
#include <assert.h>
#include <fcntl.h>
#include <gelf.h>
#include <inttypes.h>
#include <libdwfl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <fuzzer/FuzzedDataProvider.h>

// Callback function
int callback(Dwfl_Frame *state, void *arg) {
  bool isactivation;
  Dwarf_Addr pc = dwfl_frame_pc(state, &isactivation);
  Dwarf_Addr bias;
  Dwfl_Module *mod = dwfl_addrmodule(dwfl, pc);
  Dwarf_Addr start;
  const char *name = dwfl_module_info(mod, NULL, &start, NULL, NULL, NULL, NULL, NULL);
  return 0;
}

void fuzz_logic(char *filename, int open_flags, Elf_Cmd cmd) {
  (void)elf_version(EV_CURRENT);
  int fd = open(filename, open_flags);
  Elf *elf = elf_begin(fd, cmd, NULL);
  if (elf != NULL) {
    size_t elf_size = 0;
    elf_rawfile(elf, &elf_size);

    // Initialize dwfl
    static const Dwfl_Callbacks proc_callbacks = {
      .find_elf = dwfl_linux_proc_find_elf,
      .find_debuginfo = dwfl_standard_find_debuginfo
    };
    Dwfl *dwfl = dwfl_begin(&proc_callbacks);
    if (dwfl != NULL) {
      int tid = 1;
      dwfl_getthread_frames(dwfl, tid, callback, NULL);
      dwfl_end(dwfl);
    }
    elf_end(elf);
  }
  close(fd);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char filename[] = "/tmp/fuzz-libdwfl.XXXXXX";
  int fd;
  ssize_t n;

  fd = mkstemp(filename);
  assert(fd >= 0);

  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();
  n = write(fd, bytes.data(), bytes.size());
  assert(n == (ssize_t)bytes.size());

  close(fd);

  fuzz_logic(filename, O_RDONLY, ELF_C_READ);
  fuzz_logic(filename, O_RDONLY | O_WRONLY, ELF_C_RDWR);
  fuzz_logic(filename, O_RDONLY, ELF_C_READ_MMAP);
  fuzz_logic(filename, O_RDONLY | O_WRONLY, ELF_C_RDWR_MMAP);

  unlink(filename);
  return 0;
}