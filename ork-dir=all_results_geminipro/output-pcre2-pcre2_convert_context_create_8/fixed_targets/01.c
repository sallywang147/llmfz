#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <pcre2.h>

extern "C" {
#include <libfuzzer/libfuzzer_macro.h>
}

struct pcre2_real_convert_context_8 *
pcre2_convert_context_create_8(struct pcre2_real_general_context_8 *gcontext) {
  return pcre2_convert_context_create(gcontext, NULL);
}

DEFINE_PROTO_FUZZER(LLVMFuzzerTestOneInput) {
  struct pcre2_real_general_context_8 *gcontext =
      pcre2_real_general_context_create_8(NULL, NULL);
  struct pcre2_real_convert_context_8 *ccontext =
      pcre2_convert_context_create_8(gcontext);
  pcre2_real_convert_context_free_8(ccontext);
  pcre2_real_general_context_free_8(gcontext);
}