#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "FLAC/stream_decoder.h"
#include "FLAC/metadata.h"
}

static int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FLAC__Metadata_Chain *chain = FLAC__metadata_chain_new();
  if (chain == NULL) {
    return 0;
  }
  FLAC__IOCallbacks callbacks = {0};
  callbacks.read = (FLAC__IOCallback_Read)fread;
  callbacks.seek = (FLAC__IOCallback_Seek)fseek;
  callbacks.tell = (FLAC__IOCallback_Tell)ftell;
  callbacks.eof = (FLAC__IOCallback_Eof)feof;
  callbacks.close = (FLAC__IOCallback_Close)fclose;
  FILE *file = tmpfile();
  fwrite(data, 1, size, file);
  fseek(file, 0, SEEK_SET);
  FLAC__metadata_chain_read_with_callbacks(chain, (char *)file, &callbacks);
  FLAC__metadata_chain_delete(chain);
  fclose(file);
  return 0;
}