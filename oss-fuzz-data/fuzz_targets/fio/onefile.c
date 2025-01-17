#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size);

int main(int argc, char **argv) {
  FILE *fp;
  uint8_t *data;
  size_t size;

  if (argc != 2)
    return 1;

  /* opens the file, get its size, and reads it into a buffer */
  fp = fopen(argv[1], "rb");
  if (fp == NULL)
    return 2;

  if (fseek(fp, 0L, SEEK_END) != 0) {
    fclose(fp);
    return 2;
  }
  size = ftell(fp);
  if (size == (size_t)-1) {
    fclose(fp);
    return 2;
  }
  if (fseek(fp, 0L, SEEK_SET) != 0) {
    fclose(fp);
    return 2;
  }
  data = malloc(size);
  if (data == NULL) {
    fclose(fp);
    return 2;
  }
  if (fread(data, size, 1, fp) != 1) {
    fclose(fp);
    free(data);
    return 2;
  }

  /* launch fuzzer */
  LLVMFuzzerTestOneInput(data, size);
  free(data);
  fclose(fp);

  return 0;
}
