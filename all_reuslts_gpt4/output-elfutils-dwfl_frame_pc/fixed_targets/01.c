#include <assert.h>
#include <dwarf.h>
#include <elfutils/libdwfl.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fuzzer/FuzzedDataProvider.h>

void fuzz_logic_one(char *filename) {
  (void)elf_version(EV_CURRENT);
  int fd = open(filename, O_RDONLY);
  Elf *elf = elf_begin(fd, ELF_C_READ, NULL);
  if (elf != NULL) {
    size_t strndx;
    elf_getshdrstrndx(elf, &strndx);

    Elf_Scn *scn = NULL;
    // Iterate through sections
    while ((scn = elf_nextscn(elf, scn)) != NULL) {
      GElf_Shdr mem;
      GElf_Shdr *shdr = gelf_getshdr(scn, &mem);
      const char *name = elf_strptr(elf, strndx, shdr->sh_name);

      // Two options for reading sections. We keep the code structure
      // so it resembles the test code.
      // Compress and get data of the section
      if ((shdr->sh_flags & SHF_COMPRESSED) != 0) {
        if (elf_compress(scn, 0, 0) >= 0) {
          elf_getdata(scn, NULL);
        }
      } else if (name != NULL) {
        if (name[0] == '.' && name[1] == 'z') {
          if (elf_compress_gnu(scn, 0, 0) >= 0) {
            elf_getdata(scn, NULL);
          }
        }
      }
    }
    elf_end(elf);
  }
  close(fd);
}

void fuzz_logic_twice(char *filename, int open_flags, Elf_Cmd cmd) {
  (void)elf_version(EV_CURRENT);
  int fd = open(filename, open_flags);
  Elf *elf = elf_begin(fd, cmd, NULL);
  if (elf != NULL) {
    size_t elf_size = 0;
    elf_rawfile(elf, &elf_size);
    elf_end(elf);
  }
  close(fd);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char filename[] = "/tmp/fuzz-libelf.XXXXXX";
  int fd;
  ssize_t n;

  fd = mkstemp(filename);
  assert(fd >= 0);

  n = write_retry(fd, data, size);
  assert(n == (ssize_t)size);

  close(fd);

  fuzz_logic_one(filename);
  fuzz_logic_twice(filename, O_RDONLY, ELF_C_READ);
  fuzz_logic_twice(filename, O_RDONLY | O_WRONLY, ELF_C_RDWR);
  fuzz_logic_twice(filename, O_RDONLY, ELF_C_READ_MMAP);
  fuzz_logic_twice(filename, O_RDONLY | O_WRONLY, ELF_C_RDWR_MMAP);

  unlink(filename);
  return 0;
}