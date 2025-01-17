#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include "signkey.h"
}

static int fuzz_wrapfd_read(int fd, void *buf, size_t count) {
  return read(fd, buf, count);
}

static int fuzz_wrapfd_write(int fd, const void *buf, size_t count) {
  return write(fd, buf, count);
}

static int fuzz_wrapfd_close(int fd) {
  return close(fd);
}

static int signkey_generate(int keytype, int bits, char *filename, int skip_exist) {
  int fd;
  if (skip_exist) {
    struct stat st;
    if (stat(filename, &st) == 0) {
      return 0;
    }
  }
  fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
  if (fd < 0) {
    return -1;
  }
  if (signkey_generate_fd(keytype, bits, fd) < 0) {
    close(fd);
    return -1;
  }
  close(fd);
  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char filename[128];
  snprintf(filename, sizeof(filename), "/tmp/signkey-fuzz-%d", getpid());
  signkey_generate(SIGNKEY_TYPE_RSA, 2048, filename, 1);
  return 0;
}