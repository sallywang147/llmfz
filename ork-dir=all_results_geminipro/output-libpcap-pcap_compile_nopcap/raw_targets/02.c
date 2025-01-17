#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <pcap/pcap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }
  int snaplen = data[0];
  if (size < 2) {
    return 0;
  }
  int linktype = data[1];
  if (size < 3) {
    return 0;
  }
  size_t filterSize = data[2];
  if (size < 3 + filterSize) {
    return 0;
  }
  char *filter = new char[filterSize + 1];
  memcpy(filter, data + 3, filterSize);
  filter[filterSize] = '\0';
  struct bpf_program program;
  pcap_compile_nopcap(snaplen, linktype, &program, filter, 1, PCAP_NETMASK_UNKNOWN);
  delete[] filter;
  return 0;
}