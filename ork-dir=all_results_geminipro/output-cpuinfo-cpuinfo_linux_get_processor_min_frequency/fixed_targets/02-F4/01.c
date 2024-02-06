#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <linux/api.h>
#include <x86/linux/api.h>

extern "C" {
#include <cpuinfo.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char filename[256];
  sprintf(filename, "/tmp/libfuzzer.config");

  FILE *fp = fopen(filename, "wb");
  if (!fp) {
    return 0;
  }
  fwrite(data, size, 1, fp);
  fclose(fp);

  struct cpuinfo_x86_linux_processor processors[256];
  cpuinfo_x86_linux_parse_proc_cpuinfo(256, processors);
  return 0;
}