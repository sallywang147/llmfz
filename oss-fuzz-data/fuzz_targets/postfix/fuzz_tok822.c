/* Copyright 2021 Google LLC
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
      http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys_defs.h>

#include <vstring.h>

#include "lex_822.h"
#include "quote_822_local.h"
#include "tok822.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  char *new_str = (char *)malloc(size + 1);
  if (new_str == NULL) {
    return 0;
  }
  memcpy(new_str, data, size);
  new_str[size] = '\0';

  VSTRING *vp = vstring_alloc(100);
  TOK822 *list = NULL;
  list = tok822_parse_limit(new_str, 10);
  tok822_internalize(vp, list, TOK822_STR_DEFL);
  tok822_externalize(vp, list, TOK822_STR_DEFL | TOK822_STR_TRNC);
  tok822_externalize(vp, list, TOK822_STR_DEFL | TOK822_STR_LINE | TOK822_STR_TRNC);
  tok822_free_tree(list);
  vstring_free(vp);

  free(new_str);
  return 0;
}
