#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pcap/pcap.h>

FILE *
pcap_compile_nopcap(int snaplen_arg, int linktype_arg, struct bpf_program * program, char * buf, int optimize, int mask) {
  return NULL;
}

extern "C" {
#include <pcap/pcap.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  pcap_compile_nopcap(0, 0, NULL, NULL, 0, 0);
  return 0;
}