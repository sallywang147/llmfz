#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdbool.h>
#include <stdlib.h>

#define LOGMODULE test
#include "tcti/tcti-fuzzing.h"
#include "test.h"
#include "tss2-fapi/tss2_fapi.h"
#include "tss2_tcti.h"
#include "util/log.h"

#include "test-common.h"

extern "C" {
#include "tss2_fapi.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  TSS2_TEST_FAPI_CONTEXT *test_fapi_ctx;
  TSS2_TCTI_FUZZING_CONTEXT *tcti_fuzzing = NULL;
  TSS2_RC rc;
  int ret;

  ret = test_fapi_setup(&test_fapi_ctx);
  if (ret != 0) {
    return ret;
  }

  ret = test_fapi_checks_pre(test_fapi_ctx);
  if (ret != 0) {
    return ret;
  }

  tcti_fuzzing = tcti_fuzzing_context_cast(test_fapi_ctx->tcti_ctx);
  tcti_fuzzing->data = Data;
  tcti_fuzzing->size = Size;

  rc = test_invoke_fapi(test_fapi_ctx->fapi_ctx);
  if (rc != 0 && ret != 77) {
    LOG_ERROR("Test returned %08x", rc);
    exit(1);
  }

  ret = test_fapi_checks_post(test_fapi_ctx);
  if (ret != 0) {
    exit(1);
  }

  test_fapi_teardown(test_fapi_ctx);

  return 0; // Non-zero return values are reserved for future use.
}