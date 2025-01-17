#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sip.h"

extern "C" {
#include "sip_msg.h"
#include "proxy_l.h"
}

int w_forward(struct sip_msg * msg, struct proxy_l * dest) {
  printf("w_forward called\n");
  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct sip_msg msg;
  struct proxy_l dest;

  w_forward(&msg, &dest);

  return 0;
}