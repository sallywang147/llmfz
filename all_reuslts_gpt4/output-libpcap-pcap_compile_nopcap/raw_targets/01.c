#include <pcap/pcap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int snaplen_arg = stream.ConsumeIntegral<int>();
  int linktype_arg = stream.ConsumeIntegral<int>();
  int optimize = stream.ConsumeBool();
  int mask = stream.ConsumeIntegral<int>();
  std::string buf = stream.ConsumeRemainingBytesAsString();

  struct bpf_program program;

  pcap_compile_nopcap(snaplen_arg, linktype_arg, &program, const_cast<char*>(buf.c_str()), optimize, mask);

  return 0;
}