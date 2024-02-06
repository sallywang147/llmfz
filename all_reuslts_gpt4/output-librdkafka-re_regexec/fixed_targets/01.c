#include "rd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "regexp.h"
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0)
    return 0;

  FuzzedDataProvider stream(data, size);

  // Consume 1 byte for eflags
  int eflags = stream.ConsumeIntegral<unsigned char>();

  // Consume half of the remaining bytes for the pattern
  size_t pattern_size = stream.remaining_bytes() / 2;
  std::string pattern = stream.ConsumeBytesAsString(pattern_size);

  // Use the rest of the bytes for the string to be searched
  std::string search_string = stream.ConsumeRemainingBytesAsString();

  char *error;
  Reprog *prog = re_regcomp(pattern.c_str(), 0, &error);
  if (prog == NULL) {
    return 0;
  }

  Resub sub;
  sub.nsub = 10;
  sub.sub = malloc(sizeof(Resubmatch) * sub.nsub);

  re_regexec(prog, search_string.c_str(), &sub, eflags);

  free(sub.sub);
  re_regfree(prog);
  
  return 0;
}