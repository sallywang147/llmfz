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
  if (!initialized) {
    lou_registerLogCallback(avoid_log);
    initialized = 1;
  }

  FuzzedDataProvider stream(data, size);

  std::string tableList = stream.ConsumeRandomLengthString();
  std::string emphClass = stream.ConsumeRandomLengthString();

  lou_getTypeformForEmphClass(const_cast<char*>(tableList.c_str()), const_cast<char*>(emphClass.c_str()));

  return 0;
}