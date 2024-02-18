#include <assert.h>
#include <config.h>
#include <fcntl.h>
#include <internal.h>
#include <liblouis.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

#define LANGUAGE "en"

static int initialized = 0;

#define BOLDRED(x) "\x1b[31m\x1b[1m" x "\x1b[0m"

static const char *table_default;

static void __attribute__((destructor)) free_ressources(void) { lou_free(); }

void avoid_log(logLevels level, const char *msg) {
  (void)level;
  (void)msg;
}

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  int inputLen = 0;
  int outputLen = 0;
  static int counter = 0;
  if (!initialized) {
    lou_registerLogCallback(avoid_log);
    initialized = 1;
  }

  if (size < 512) {
    return 0;
  }

  // Write first half of fuzz data to a table file.
  char new_file[256];
  sprintf(new_file, "/tmp/libfuzzer-%d.ctb", counter);
  counter++;

  FILE *fp = fopen(new_file, "wb");
  if (!fp) {
    return 0;
  }
  fwrite(data, 512, 1, fp);
  fclose(fp);

  // Adjust data pointer to after the table file data.
  data += 512;
  size -= 512;

  /* check if this works, otherwise bail */
  if (lou_checkTable(new_file) == 0) {
    lou_free();
    unlink(new_file);
    return 0;
  }
  char *mutable_data = NULL;
  table_default = new_file;

  mutable_data = strndup((char *)data, size);
  if (!mutable_data) {
    perror("malloc");
    exit(1);
  }

  widechar *inbufx = malloc((size * 16 + 1) * sizeof(widechar));
  int len = (int)_lou_extParseChars(mutable_data, inbufx);
  free(mutable_data);
  if (len <= 0) {
    free(inbufx);
    unlink(new_file);
    lou_free();
    return -1;
  }

  assert(len <= (size * 16));
  inputLen = len;
  outputLen = len * 16;
  widechar *outbuf = malloc((outputLen + 1) * sizeof(widechar));
  short *typeform = NULL;
  char *spacing = NULL;
  int *outputPos = NULL;
  int *inputPos = NULL;
  int *cursorPos = NULL;
  char *inputHyphens = NULL;
  char *outputHyphens = NULL;
  int mode = stream.ConsumeIntegral<int>();

  lou_translatePrehyphenated((char *)table_default, inbufx, &inputLen, outbuf, &outputLen, typeform, spacing, outputPos, inputPos, cursorPos, inputHyphens, outputHyphens, mode);

  free(inbufx);
  free(outbuf);

  lou_free();
  unlink(new_file);

  return 0;
}