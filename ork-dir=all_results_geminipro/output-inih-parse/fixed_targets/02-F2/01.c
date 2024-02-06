#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
}

void parse(char *fname) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(fname, "r");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, fp)) != -1) {
    // Do something with the line
    printf("%s", line);
  }

  fclose(fp);
  if (line) {
    free(line);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  std::string filename = fdp.ConsumeRandomLengthString(16);
  FILE *fp = fdp.ConsumeFile(filename.c_str());
  if (fp) {
    parse(filename.c_str());
    fclose(fp);
  }
  return 0;
}