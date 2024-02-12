 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

int main2(int argc, char **argv) {
  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 24) {
    return 0;
  }
  char *opt_fuzz = malloc(24);

  memcpy(opt_fuzz, data, 23);
  opt_fuzz[23] = 0;
  data += 23;
  size -= 23;

  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';
  char *my_argv[4];
  my_argv[0] = "/tmp/fuzz/";
  my_argv[1] = opt_fuzz;
  my_argv[2] = new_str;
  my_argv[3] = NULL;

  main2(3, my_argv);

  free(new_str);
  free(opt_fuzz);
  return 0;
}