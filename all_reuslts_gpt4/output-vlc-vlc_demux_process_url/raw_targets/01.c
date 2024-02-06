#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "src/input/demux-run.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerInitialize(int *argc, char ***argv);
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

static struct vlc_run_args args;

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  (void)argc;
  (void)argv;

  vlc_run_args_init(&args);

  return 0;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string url = stream.ConsumeRemainingBytesAsString();
  vlc_demux_process_url(&args, url.c_str());
  return 0;
}