#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <pcap/pcap.h>

FILE *outfile = NULL;

static int bufferToFile(const char *name, const uint8_t *Data, size_t Size) {
  FILE *fd;
  if (remove(name) != 0) {
    if (errno != ENOENT) {
      printf("failed remove, errno=%d\n", errno);
      return -1;
    }
  }
  fd = fopen(name, "wb");
  if (fd == NULL) {
    printf("failed open, errno=%d\n", errno);
    return -2;
  }
  if (fwrite(Data, 1, Size, fd) != Size) {
    fclose(fd);
    return -3;
  }
  fclose(fd);
  return 0;
}

void fuzz_openFile(const char *name) {
  if (outfile != NULL) {
    fclose(outfile);
  }
  outfile = fopen(name, "w");
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  pcap_t *pkts;
  char errbuf[PCAP_ERRBUF_SIZE];
  char filename[FILENAME_MAX] = {0};
  const u_char *pkt;
  struct pcap_pkthdr *header;
  int fd = -1, r;
  size_t filterSize;
  char *filter;
  struct bpf_program bpf;

  // initialize output file
  if (outfile == NULL) {
    outfile = fopen("/dev/null", "w");
    if (outfile == NULL) {
      return 0;
    }
  }

  if (Size < 1) {
    return 0;
  }
  filterSize = Data[0];
  if (Size < 1 + filterSize || filterSize == 0) {
    return 0;
  }

  // generate temporary file name
  snprintf(filename, FILENAME_MAX, "/tmp/libpcap_fuzz_both.XXXXXX");
  if ((fd = mkstemp(filename)) < 0) {
    return 0;
  }
  close(fd);

  // rewrite buffer to a file as libpcap does not have buffer inputs
  if (bufferToFile(filename, Data + 1 + filterSize, Size - (1 + filterSize)) < 0) {
    unlink(filename);
    return 0;
  }

  // initialize structure
  pkts = pcap_open_offline(filename, errbuf);
  if (pkts == NULL) {
    fprintf(outfile, "Couldn't open pcap file %s\n", errbuf);
    unlink(filename);
    return 0;
  }

  filter = malloc(filterSize);
  memcpy(filter, Data + 1, filterSize);
  // null terminate string
  filter[filterSize - 1] = 0;

  if (pcap_compile(pkts, &bpf, filter, 1, PCAP_NETMASK_UNKNOWN) == 0) {
    // loop over packets
    r = pcap_next_ex(pkts, &header, &pkt);
    while (r > 0) {
      // checks filter
      fprintf(outfile, "packet length=%d/%d filter=%d\n", header->caplen, header->len, pcap_offline_filter(&bpf, header, pkt));
      r = pcap_next_ex(pkts, &header, &pkt);
    }
    // close structure
    pcap_close(pkts);
    pcap_freecode(&bpf);
  } else {
    pcap_close(pkts);
  }
  free(filter);

  unlink(filename);
  return 0;
}
