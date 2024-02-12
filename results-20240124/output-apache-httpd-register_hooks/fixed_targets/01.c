#include "apr.h"
#include "apr_file_io.h"
#include "apr_poll.h"
#include "apr_portable.h"
#include "apr_proc_mutex.h"
#include "apr_signal.h"
#include "apr_strings.h"
#include "apr_thread_mutex.h"
#include "apr_thread_proc.h"

#define APR_WANT_STRFUNC
#include "apr_file_io.h"
#include "apr_fnmatch.h"
#include "apr_want.h"

#include "apr_poll.h"
#include "apr_want.h"

#include "ap_config.h"
#include "ap_expr.h"
#include "ap_listen.h"
#include "ap_provider.h"
#include "ap_regex.h"

#include <string.h>
#include <unistd.h>

#include "ada_fuzz_header.h"

extern "C" {
#include "mod_authn_core.h"
#include "apr_strings.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // Initialize fuzzing garbage collector. We use this to easily
  // get data types seeded with random input from the fuzzer.
  af_gb_init();

  const uint8_t *data2 = data;
  size_t size2 = size;

  char *new_str = af_gb_get_null_terminated(&data2, &size2);

  if (new_str != NULL) {
    size_t new_str_len = strlen(new_str);

    // Targets that do not require a pool

    ap_cstr_casecmp(new_str, new_str);
    if (new_str_len > 2) {
      ap_cstr_casecmpn(new_str, new_str + 2, new_str_len - 2);
    }
    ap_strcmp_match(new_str, new_str);
    ap_strcasecmp_match(new_str, new_str);
    ap_strcasestr(new_str, new_str);

    apr_interval_time_t timeout;
    ap_timeout_parameter_parse(new_str, &timeout, "ms");

    // Pool initialisation
    if (apr_pool_initialize() == APR_SUCCESS) {
      apr_pool_t *pool = NULL;
      apr_pool_create(&pool, NULL);

      // Targets that require a pool

      ap_field_noparam(pool, new_str);

      ap_escape_shell_cmd(pool, new_str);
      ap_os_escape_path(pool, new_str, 0);
      ap_escape_html2(pool, new_str, 0);
      ap_escape_logitem(pool, new_str);

      // This line causes some issues if something bad is allocated
      ap_escape_quotes(pool, new_str);

      // base64
      ap_pbase64decode(pool, new_str);
      ap_pbase64encode(pool, new_str);

      // List functions
      const char *tmp_s = new_str;
      ap_get_list_item(pool, &tmp_s);
      ap_find_list_item(pool, new_str, "kjahsdfkj");
      ap_find_token(pool, new_str, "klsjdfk");
      ap_find_last_token(pool, new_str, "sdadf");
      apr_array_header_t *offers = NULL;
      ap_parse_token_list_strict(pool, new_str, &offers, 0);

      tmp_s = new_str;
      ap_get_token(pool, &tmp_s, 1);

      tmp_s = NULL;
      ap_pstr2_alnum(pool, new_str, &tmp_s);

      ap_is_chunked(pool, new_str);

      // Word functions
      tmp_s = new_str;
      ap_getword(pool, &tmp_s, 0);
      tmp_s = new_str;
      ap_getword_conf2(pool, &tmp_s);

      ap_escape_urlencoded(pool, new_str);

      // Fuzzer logic here
      register_hooks(pool);
      // Fuzzer logic end

      // Cleanup
      apr_pool_terminate();
    }
  }

  // Cleanup all of the memory allocated by the fuzz headers.
  af_gb_cleanup();
  return 0;
}