#include <fuzzer/FuzzedDataProvider.h>
#include <libbpf.h>

static int libbpf_print_fn(enum libbpf_print_level level, const char *format, va_list args) { return 0; }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string path = stream.ConsumeRandomLengthString();
  
  libbpf_set_print(libbpf_print_fn);

  struct bpf_object *obj = bpf_object__open((char *)path.c_str());
  
  if (obj != nullptr) {
    bpf_object__close(obj);
  }

  return 0;
}