#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <resolv.h>

#include "ub_ctx.h"

extern "C" {
#include "ub_resolve.h"
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct ub_ctx *ctx;
  struct ub_result *result;
  char name[256];
  int rrtype = 1;
  int rrclass = 1;

  ctx = ub_ctx_create();
  if (!ctx) {
    perror("ub_ctx_create");
    exit(1);
  }

  memcpy(name, data, size);
  name[size] = '\0';

  int ret = ub_resolve(ctx, name, rrtype, rrclass, &result);
  if (ret < 0) {
    perror("ub_resolve");
    exit(1);
  }

  ub_result_free(result);
  ub_ctx_delete(ctx);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <domain name>\n", argv[0]);
    exit(1);
  }

  LLVMFuzzerTestOneInput((const uint8_t *)argv[1], strlen(argv[1]));

  return 0;
}