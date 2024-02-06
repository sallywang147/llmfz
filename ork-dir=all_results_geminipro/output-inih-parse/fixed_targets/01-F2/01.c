#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <libFuzzer/libFuzzer.h>
}

void parse(char *fname) {
  FILE *fp;
  char buf[1024];

  fp = fopen(fname, "r");
  if (fp == NULL) {
    perror("fopen");
    exit(1);
  }

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0';
    }
    printf("%s\n", buf);
  }

  fclose(fp);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1 || size > 1024) {
    return 0;
  }

  char *fname = (char *)malloc(size + 1);
  memcpy(fname, data, size);
  fname[size] = '\0';

  parse(fname);

  free(fname);

  return 0;
}