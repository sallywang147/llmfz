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
  std::string tableListStr = stream.ConsumeRandomLengthString();
  char* tableList = tableListStr.c_str();

  if (!initialized) {
    lou_registerLogCallback(avoid_log);
    initialized = 1;
  }

  char **emphClasses = lou_getEmphClasses(tableList);

  if (emphClasses != NULL) {
    int i = 0;
    while (emphClasses[i] != NULL) {
      free(emphClasses[i]);
      i++;
    }
    free(emphClasses);
  }

  lou_free();

  return 0;
}