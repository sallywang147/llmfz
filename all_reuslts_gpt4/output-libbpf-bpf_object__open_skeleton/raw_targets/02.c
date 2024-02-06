#include "libbpf.h"
#include "fuzzer/FuzzedDataProvider.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the skeleton object
  struct bpf_object_skeleton *skeleton = nullptr;

  // Define and initialize the options object
  struct bpf_object_open_opts opts;
  opts.sz = stream.ConsumeIntegral<size_t>();
  opts.object_name = stream.ConsumeRandomLengthString().c_str();
  opts.relaxed_maps = stream.ConsumeBool();
  opts.relaxed_core_relocs = stream.ConsumeBool();
  opts.pin_root_path = stream.ConsumeRandomLengthString().c_str();
  opts.attach_prog_fd = stream.ConsumeIntegral<int>();
  opts.file = stream.ConsumeRandomLengthString().c_str();
  opts.prog_cnt = stream.ConsumeIntegral<unsigned int>();
  opts.map_cnt = stream.ConsumeIntegral<unsigned int>();
  opts.prog_sec = stream.ConsumeRandomLengthString().c_str();
  opts.map_def_sz = stream.ConsumeIntegral<size_t>();
  opts.map_defs = nullptr; // Not providing map definitions for fuzzing
  opts.data = stream.ConsumeRemainingBytes<uint8_t>().data();
  opts.datasz = stream.remaining_bytes();

  libbpf_set_print(libbpf_print_fn);

  // Call the function to fuzz
  int ret = bpf_object__open_skeleton(skeleton, &opts);

  return 0;
}