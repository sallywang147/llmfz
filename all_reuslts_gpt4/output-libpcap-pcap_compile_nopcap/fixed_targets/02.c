#include <pcap/pcap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int snaplen_arg = stream.ConsumeIntegral<int>();
  int linktype_arg = stream.ConsumeIntegral<int>();
  int optimize = stream.ConsumeBool();
  int mask = stream.ConsumeIntegral<int>();

  // Extract a string
  std::string buf = stream.ConsumeRandomLengthString();
  char *buf_ptr = const_cast<char *>(buf.c_str());

  // Initialize a bpf_program structure
  struct bpf_program program;

  // Call the target function
  pcap_compile_nopcap(snaplen_arg, linktype_arg, &program, buf_ptr, optimize, mask);

  return 0;
}