 #include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 16) {
    return 0;
  }
  char *arg_fuzz = malloc(16);

  memcpy(arg_fuzz, data, 15);
  arg_fuzz[15] = 0;
  data += 15;
  size -= 15;

  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  char *my_argv[3];
  my_argv[0] = "/tmp/fuzz/";
  my_argv[1] = arg_fuzz;
  my_argv[2] = new_str;

  main2(3, my_argv);

  free(new_str);
  free(arg_fuzz);
  return 0;
}