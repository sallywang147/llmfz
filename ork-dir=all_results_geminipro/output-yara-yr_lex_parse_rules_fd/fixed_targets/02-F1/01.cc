#include <stddef.h>
#include <stdint.h>
#include <yara.h>

extern "C" {
#include <yara/libyara.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  YR_COMPILER *compiler;

  if (yr_initialize() != ERROR_SUCCESS)
    return 0;

  if (yr_compiler_create(&compiler) != ERROR_SUCCESS)
    return 0;

  yr_lex_parse_rules_fd(0, compiler);

  yr_compiler_destroy(compiler);

  return 0;
}