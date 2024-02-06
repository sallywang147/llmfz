#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "regex.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct parse parse_obj;
  parse_obj.g = (struct re_guts *)malloc(sizeof(struct re_guts));
  if (!parse_obj.g) {
    return 0;
  }

  parse_obj.g->strip = (sop *)malloc(sizeof(sop));
  if (!parse_obj.g->strip) {
    free(parse_obj.g);
    return 0;
  }

  parse_obj.g->sets = (cset *)malloc(sizeof(cset));
  if (!parse_obj.g->sets) {
    free(parse_obj.g->strip);
    free(parse_obj.g);
    return 0;
  }

  parse_obj.g->setbits = (uch *)malloc(sizeof(uch));
  if (!parse_obj.g->setbits) {
    free(parse_obj.g->sets);
    free(parse_obj.g->strip);
    free(parse_obj.g);
    return 0;
  }

  parse_obj.next = (char *)stream.ConsumeRemainingBytesAsString().c_str();
  parse_obj.end = parse_obj.next + size;
  parse_obj.error = 0;
  parse_obj.ncsalloc = 0;

  nonnewline(&parse_obj);

  free(parse_obj.g->setbits);
  free(parse_obj.g->sets);
  free(parse_obj.g->strip);
  free(parse_obj.g);

  return 0;
}