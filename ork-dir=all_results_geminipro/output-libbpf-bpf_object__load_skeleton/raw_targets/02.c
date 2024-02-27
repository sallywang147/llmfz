#include "libbpf.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct bpf_object_skeleton *s = NULL;
  DECLARE_LIBBPF_OPTS(bpf_object_open_opts, opts);
  int err;

  libbpf_set_print(libbpf_print_fn);

  opts.object_name = "fuzz-object";
  s = bpf_object__open_mem(data, size, &opts);
  err = libbpf_get_error(s);
  if (err)
    return 0;

  err = bpf_object__load_skeleton(s);
  if (err)
    return 0;

  bpf_object__close(s);
  return 0;
}