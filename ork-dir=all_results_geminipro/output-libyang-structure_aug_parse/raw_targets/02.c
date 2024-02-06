#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "libyang.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct lysp_ctx *pctx = NULL;
  struct lysp_ext_instance *ext = NULL;
  static bool log = false;

  if (!log) {
    ly_log_options(0);
    log = true;
  }

  pctx = lysp_ctx_new(NULL);
  if (!pctx) {
    fprintf(stderr, "Failed to create context\n");
    exit(EXIT_FAILURE);
  }

  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes();
  void *data_ptr = bytes.data();

  ext = lysp_ext_instance_new(pctx);
  if (!ext) {
    fprintf(stderr, "Failed to create extension instance\n");
    exit(EXIT_FAILURE);
  }

  int ret = structure_aug_parse(pctx, ext);
  if (ret != LY_SUCCESS) {
    fprintf(stderr, "Failed to parse structure augmentation: %s\n", lys_err_str(ret));
    exit(EXIT_FAILURE);
  }

  lysp_ext_instance_free(ext);
  lysp_ctx_free(pctx);

  return 0;
}