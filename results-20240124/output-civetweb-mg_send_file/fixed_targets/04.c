#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "civetweb.h"

extern "C" {
#include "civetweb.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct mg_connection conn;
  memset(&conn, 0, sizeof(conn));
  mg_send_file(&conn, (char*)data);
  return 0;
}
}

int main() {
  return 0;
}