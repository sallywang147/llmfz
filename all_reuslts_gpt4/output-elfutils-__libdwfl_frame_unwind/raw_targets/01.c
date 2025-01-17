#include <assert.h>
#include <fcntl.h>
#include <inttypes.h>
#include <libdwfl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fuzzer/FuzzedDataProvider.h>

void fuzz_logic_one(char *filename) {
  (void)elf_version(EV_CURRENT);
  int fd = open(filename, O_RDONLY);
  Dwfl *dwfl = dwfl_begin(&dwfl_callbacks);
  if (dwfl != NULL) {
    Dwfl_Module *mod = dwfl_report_offline(dwfl, "fuzz", filename, fd);
    if (mod != NULL) {
      dwfl_report_end(dwfl, NULL, NULL);
      dwfl_getmodules(dwfl, [](Dwfl_Module *mod, void **userdata, const char *name, Dwarf_Addr base) {
        Dwfl_Frame *state = dwfl_framestate_new(mod, base);
        if (state != NULL) {
          __libdwfl_frame_unwind(state);
          dwfl_framestate_free(state);
        }
        return 0;
      }, NULL, 0);
    }
    dwfl_end(dwfl);
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

  fuzz_logic_one(filename);

  unlink(filename);
  return 0;
}