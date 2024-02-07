/*
   +----------------------------------------------------------------------+
   | Copyright (c) The PHP Group                                          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | https://www.php.net/license/3_01.txt                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Nikita Popov <nikic@php.net>                                |
   +----------------------------------------------------------------------+
 */

#include "fuzzer-execute-common.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size > MAX_SIZE) {
    /* Large inputs have a large impact on fuzzer performance,
     * but are unlikely to be necessary to reach new codepaths. */
    return 0;
  }

  zend_string *jit_option = ZSTR_INIT_LITERAL("opcache.jit", 1);

  /* First run without JIT to determine whether we bail out. We should not run JITed code if
   * we bail out here, as the JIT code may loop infinitely. */
  steps_left = MAX_STEPS;
  bailed_out = false;
  zend_alter_ini_entry_chars(jit_option, "off", sizeof("off") - 1, PHP_INI_USER, PHP_INI_STAGE_RUNTIME);
  fuzzer_do_request_from_buffer(FILE_NAME, (const char *)Data, Size, /* execute */ 1, opcache_invalidate);

  if (!bailed_out) {
    steps_left = MAX_STEPS;
    zend_alter_ini_entry_chars(jit_option, "tracing", sizeof("tracing") - 1, PHP_INI_USER, PHP_INI_STAGE_RUNTIME);
    zend_execute_ex = orig_execute_ex;
    /* Trace & compile */
    fuzzer_do_request_from_buffer(FILE_NAME, (const char *)Data, Size, /* execute */ 1, NULL);
    /* Execute trace */
    fuzzer_do_request_from_buffer(FILE_NAME, (const char *)Data, Size, /* execute */ 1, opcache_invalidate);
    zend_execute_ex = fuzzer_execute_ex;
  }

  zend_string_release(jit_option);

  return 0;
}

int LLVMFuzzerInitialize(int *argc, char ***argv) {
  char *opcache_path = get_opcache_path();
  assert(opcache_path && "Failed to determine opcache path");

  char ini_buf[512];
  snprintf(ini_buf, sizeof(ini_buf),
           "zend_extension=%s\n"
           "opcache.validate_timestamps=0\n"
           "opcache.file_update_protection=0\n"
           "opcache.memory_consumption=1024\n"
           "opcache.jit_buffer_size=128M\n"
           "opcache.jit_hot_func=1\n"
           "opcache.jit_hot_loop=1\n"
           "opcache.jit_hot_return=1\n"
           "opcache.jit_hot_side_exit=1\n"
           "opcache.jit_max_root_traces=100000\n"
           "opcache.jit_max_side_traces=100000\n"
           "opcache.jit_max_exit_counters=100000\n"
           "opcache.protect_memory=1\n",
           opcache_path);
  free(opcache_path);

  create_file();
  fuzzer_init_php_for_execute(ini_buf);
  return 0;
}
