#include "libbpf.h"
#include <fuzzer/FuzzedDataProvider.h>

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct bpf_object *obj = NULL;
  DECLARE_LIBBPF_OPTS(bpf_object_open_opts, opts);
  int err;

  libbpf_set_print(libbpf_print_fn);

  FuzzedDataProvider provider(data, size);
  opts.object_name = "fuzz-object";
  obj = bpf_object__open_mem(data, size, &opts);
  err = libbpf_get_error(obj);
  if (err)
    return 0;

  int extra_log_level = provider.ConsumeIntegral<int>();
  std::string target_btf_path = provider.ConsumeRemainingBytesAsString();
  bpf_object_load(obj, extra_log_level, target_btf_path.c_str());

  bpf_object__close(obj);
  return 0;
}