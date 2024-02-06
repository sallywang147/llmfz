#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdbool.h>
#include <stdlib.h>

#define LOGMODULE test
#include "tcti/tcti-fuzzing.h"
#include "test.h"
#include "tss2-esys/esys_util.h"
#include "tss2_esys.h"
#include "tss2_tcti.h"
#include "util/log.h"

#include "test-common.h"

extern "C" {
#include "tss2_tcti_fuzzing.h"
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  TSS2_TEST_ESYS_CONTEXT *test_esys_ctx;
  TSS2_TCTI_FUZZING_CONTEXT *tcti_fuzzing = NULL;
  TSS2_RC rc;
  int ret;

  ret = test_esys_setup(&test_esys_ctx);
  if (ret != 0) {
    return ret;
  }

  ret = test_esys_checks_pre(test_esys_ctx);
  if (ret != 0) {
    return ret;
  }

  tcti_fuzzing = tcti_fuzzing_context_cast(test_esys_ctx->esys_ctx->tcti_ctx);
  tcti_fuzzing->data = Data;
  tcti_fuzzing->size = Size;

  rc = test_invoke_esys(test_esys_ctx->esys_ctx);
  if (rc != 0 && ret != 77) {
    LOG_ERROR("Test returned %08x", rc);
    exit(1);
  }

  ret = test_esys_checks_post(test_esys_ctx);
  if (ret != 0) {
    exit(1);
  }

  test_esys_teardown(test_esys_ctx);

  return 0; // Non-zero return values are reserved for future use.
}