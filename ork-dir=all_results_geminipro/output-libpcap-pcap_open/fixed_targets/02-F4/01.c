#include <pcap/pcap.h>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 1) {
    return 0;
  }
  char *source = (char *)malloc(Size);
  memcpy(source, Data, Size);
  source[Size - 1] = '\0';
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *handle = pcap_open_live(source, 65535, PCAP_OPENFLAG_PROMISCUOUS, 1000, errbuf);
  if (handle == NULL) {
    fprintf(stderr, "pcap_open_live: %s\n", errbuf);
    return 0;
  }
  pcap_close(handle);
  free(source);
  return 0;
}