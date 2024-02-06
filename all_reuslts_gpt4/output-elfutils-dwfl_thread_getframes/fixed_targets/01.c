#include "system.h"
#include <assert.h>
#include <fcntl.h>
#include <gelf.h>
#include <inttypes.h>
#include <libelf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <dwarf.h>
#include <elfutils/libdwfl.h>
#include <fuzzer/FuzzedDataProvider.h>

// Callback function that will be passed to dwfl_thread_getframes
int callback(Dwfl_Frame *state, void *arg) {
  Dwarf_Addr pc;
  bool isactivation;
  dwfl_frame_pc(state, &pc, &isactivation);
  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file with the fuzzed data
  char filename[] = "/tmp/fuzz-libdwfl.XXXXXX";
  int fd = mkstemp(filename);
  assert(fd >= 0);
  write(fd, data, size);
  close(fd);

  // Initialize libdwfl
  static const Dwfl_Callbacks offline_callbacks = {
      .find_debuginfo = dwfl_standard_find_debuginfo,
      .debuginfo_path = NULL,
  };
  Dwfl *dwfl = dwfl_begin(&offline_callbacks);
  assert(dwfl != NULL);

  // Report the module to libdwfl
  int dwfl_report_result = dwfl_report_offline(dwfl, "", filename, -1);
  assert(dwfl_report_result == 0);

  // End reporting and process the ELF file
  dwfl_report_end(dwfl, NULL, NULL);
  dwfl_getmodules(dwfl, NULL, NULL, 0);

  // Get the first thread
  Dwfl_Thread *thread = dwfl_getthread(dwfl, 1);
  if (thread != NULL) {
    // Call the function to fuzz
    dwfl_thread_getframes(thread, callback, NULL);
  }

  // Clean up
  dwfl_end(dwfl);
  unlink(filename);

  return 0;
}