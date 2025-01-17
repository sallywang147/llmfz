#include "libbpf.h"
#include "fuzzer/FuzzedDataProvider.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct bpf_object_skeleton *s = nullptr; // We don't have a real skeleton to work with, so we pass nullptr
  struct bpf_object_open_opts opts;

  opts.sz = sizeof(struct bpf_object_open_opts);
  opts.object_name = stream.ConsumeRandomLengthString().c_str();
  opts.relaxed_maps = stream.ConsumeBool();
  opts.pin_root_path = stream.ConsumeRandomLengthString().c_str();
  opts.attach_prog_fd = stream.ConsumeIntegral<int>();
  opts.kconfig = stream.ConsumeRandomLengthString().c_str();

  libbpf_set_print(libbpf_print_fn);

  int result = bpf_object__open_skeleton(s, &opts);
  
  return 0;
}