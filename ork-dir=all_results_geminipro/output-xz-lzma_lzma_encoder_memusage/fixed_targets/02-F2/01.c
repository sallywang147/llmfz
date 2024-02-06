#include "fuzz_common.h"
#include "lzma.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

extern int LLVMFuzzerTestOneInput(const uint8_t *inbuf, size_t inbuf_size) {
  if (inbuf_size == 0) {
    fprintf(stderr, "no input data provided\n");
    return 0;
  }

  // Initialize lzma_options with the above preset level
  lzma_options_lzma opt_lzma;
  if (lzma_lzma_preset(&opt_lzma, LZMA_PRESET_DEFAULT)) {
    fprintf(stderr, "lzma_lzma_preset() failed\n");
    abort();
  }

  // Set the filter chain as only LZMA2.
  lzma_filter filters[2] = {{
                                .id = LZMA_FILTER_LZMA2,
                                .options = &opt_lzma,
                            },
                            {
                                .id = LZMA_VLI_UNKNOWN,
                            }};

  // Set the LZMA options based on the first input byte. The fuzzer
  // will learn through its mutational genetic algorithm with the
  // code coverage feedback that the first byte must be one of the
  // values with a switch case label. This allows us to have one fuzz
  // target cover many critical code paths so the fuzz resources can
  // be used efficiently.
  char *options = NULL;
  const uint8_t decider = inbuf[0];

  switch (decider) {
  case 0:
    options = strdup("");
    break;
  case 1:
    options = strdup("lc=0");
    break;
  case 2:
    options = strdup("lc=1");
    break;
  case 3:
    options = strdup("lc=2");
    break;
  case 4:
    options = strdup("lc=3");
    break;
  case 5:
    options = strdup("lp=0");
    break;
  case 6:
    options = strdup("lp=1");
    break;
  case 7:
    options = strdup("lp=2");
    break;
  case 8:
    options = strdup("lp=3");
    break;
  case 9:
    options = strdup("pb=0");
    break;
  case 10:
    options = strdup("pb=1");
    break;
  case 11:
    options = strdup("pb=2");
    break;
  case 12:
    options = strdup("pb=3");
    break;
  case 13:
    options = strdup("dict=1024");
    break;
  case 14:
    options = strdup("dict=2048");
    break;
  case 15:
    options = strdup("dict=4096");
    break;
  case 16:
    options = strdup("dict=8192");
    break;
  case 17:
    options = strdup("dict=16384");
    break;
  case 18:
    options = strdup("dict=32768");
    break;
  case 19:
    options = strdup("dict=65536");
    break;
  case 20:
    options = strdup("dict=131072");
    break;
  case 21:
    options = strdup("dict=262144");
    break;
  case 22:
    options = strdup("dict=524288");
    break;
  case 23:
    options = strdup("dict=1048576");
    break;
  case 24:
    options = strdup("dict=2097152");
    break;
  case 25:
    options = strdup("dict=4194304");
    break;
  case 26:
    options = strdup("dict=8388608");
    break;
  case 27:
    options = strdup("dict=16777216");
    break;
  case 28:
    options = strdup("dict=33554432");
    break;
  case 29:
    options = strdup("dict=67108864");
    break;
  case 30:
    options = strdup("dict=134217728");
    break;
  case 31:
    options = strdup("dict=268435456");
    break;
  case 32:
    options = strdup("dict=536870912");
    break;
  case 33:
    options = strdup("dict=1073741824");
    break;
  case 34:
    options = strdup("dict=2147483648");
    break;
  case 35:
    options = strdup("dict=4294967296");
    break;
  case 36:
    options = strdup("dict=8589934592");
    break;
  case 37:
    options = strdup("dict=17179869184");
    break;
  case 38:
    options = strdup("dict=34359738368");
    break;
  case 39:
    options = strdup("dict=68719476736");
    break;
  case 40:
    options = strdup("dict=137438953472");
    break;
  case 41:
    options = strdup("dict=274877906944");
    break;
  case 42:
    options = strdup("dict=549755813888");
    break;
  case 43:
    options = strdup("dict=1099511627776");
    break;
  case 44:
    options = strdup("dict=2199023255552");
    break;
  case 45:
    options = strdup("dict=4398046511104");
    break;
  case 46:
    options = strdup("dict=8796093022208");
    break;
  case 47:
    options = strdup("dict=17592186044416");
    break;
  case 48:
    options = strdup("dict=35184372088832");
    break;
  case 49:
    options = strdup("dict=70368744177664");
    break;
  case 50:
    options = strdup("dict=140737488355328");
    break;
  case 51:
    options = strdup("dict=281474976710656");
    break;
  case 52:
    options = strdup("dict=562949953421312");
    break;
  case 53:
    options = strdup("dict=1125899906842624");
    break;
  case 54:
    options = strdup("dict=2251799813685248");
    break;
  case 55:
    options = strdup("dict=4503599627370496");
    break;
  case 56:
    options = strdup("dict=9007199254740992");
    break;
  case 57:
    options = strdup("dict=18014398509481984");
    break;
  case 58:
    options = strdup("dict=36028797018963968");
    break;
  case 59:
    options = strdup("dict=720