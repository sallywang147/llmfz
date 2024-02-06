#include "../ini.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: inihfuzz file.ini\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "rb");
  if (!f) {
    printf("cannot open file %s\n", argv[1]);
    return 1;
  }
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = malloc(fsize + 1);
  fread(string, 1, fsize, f);
  fclose(f);
  string[fsize] = 0;

  char *ret = ini_reader_string(NULL, 0, string);
  printf("%s\n", ret);
  free(ret);
  free(string);
  return 0;
}

#else

#define kMinInputLength 20
#define kMaxInputLength 1024

extern int LLVMFuzzerTestOneInput(const char *Data, size_t Size) {

  if (Size < kMinInputLength || Size > kMaxInputLength) {
    return 0;
  }

  char *data = malloc(Size + 1);
  memcpy(data, Data, Size);
  data[Size] = '\0';

  char *ret = ini_reader_string(NULL, 0, data);

  free(ret);
  free(data);

  return 0;
}

#endif