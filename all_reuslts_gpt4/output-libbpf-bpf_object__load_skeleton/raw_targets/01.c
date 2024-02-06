#include "libbpf.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct bpf_object_skeleton *skeleton = NULL;
  int err;

  libbpf_set_print(libbpf_print_fn);

  skeleton = bpf_object__open_skeleton(data, size);
  if (!skeleton)
    return 0;

  err = bpf_object__load_skeleton(skeleton);
  if (err)
    return 0;

  bpf_object__destroy_skeleton(skeleton);
  return 0;
}