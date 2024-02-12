#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int scan_entity(char *buf, size_t len);

#ifdef __cplusplus
}
#endif

int main(void) {
  char buf[1024];
  scan_entity(buf, sizeof(buf));
  return 0;
}