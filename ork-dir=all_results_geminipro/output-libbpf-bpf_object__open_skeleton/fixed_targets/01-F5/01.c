#include "libbpf.h"

extern "C" {
#include "bpf_load.h"
#include "bpf_object_skeleton.h"
}

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct bpf_object_skeleton *skel = NULL;
  DECLARE_LIBBPF_OPTS(bpf_object_open_opts, opts);
  int err;

  libbpf_set_print(libbpf_print_fn);

  opts.object_name = "fuzz-object";
  err = bpf_object__open_skeleton_file(data, size, &skel, &opts);
  if (err)
    return 0;

  bpf_object__close(skel);
  return 0;
}