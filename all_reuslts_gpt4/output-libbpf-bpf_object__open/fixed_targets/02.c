#include "libbpf.h"

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  struct bpf_object *obj = NULL;
  int err;

  libbpf_set_print(libbpf_print_fn);

  FuzzedDataProvider stream(data, size);
  std::string path = stream.ConsumeRandomLengthString();
  obj = bpf_object__open((char *)path.c_str());
  err = libbpf_get_error(obj);
  if (err)
    return 0;

  bpf_object__close(obj);
  return 0;
}