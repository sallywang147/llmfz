#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include "picotls.h"
#include "picotls/openssl.h"
#include "util.h"

extern "C" {
#include "picotls/openssl/picotls_openssl.h"
}

void deterministic_random_bytes(void *buf, size_t len) {
  for (int i = 0; i < len; i++) {
    ((uint8_t *)buf)[i] = 