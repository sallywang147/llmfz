#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "hal_thread.h"
#include "iec61850_server.h"
}

int LLVMFuzzerTestOneInput(const char *data, size_t size) {
  int out;
  MmsValue *value = NULL;
  value = MmsValue_decodeMmsData(data, 0, size, &out);

  if (value != NULL) {
    char buffer[1024];
    int bufPos = 0;
    int encode = 0;
    encodeArrayAccessResult(value, buffer, bufPos, encode);
    MmsValue_delete(value);
  }

  return 0;
}

int main() {
  // Initialize the IEC 61850 server.
  iec61850_server_init();

  // Start the IEC 61850 server thread.
  hal_thread_create(&iec61850_server_thread, iec61850_server_run, NULL);

  // Wait for the IEC 61850 server thread to finish.
  hal_thread_join(iec61850_server_thread);

  // Clean up the IEC 61850 server.
  iec61850_server_cleanup();

  return 0;
}