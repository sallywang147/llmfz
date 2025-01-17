#include <fuzzer/FuzzedDataProvider.h>
#include <pcap/pcap.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    // Extract integral values
    int snaplen = stream.ConsumeIntegral<int>();
    int promisc = stream.ConsumeIntegral<int>();
    int to_ms = stream.ConsumeIntegral<int>();

    // Extract a string. You MUST use .c_str() to use result as pointer
    std::string device = stream.ConsumeRandomLengthString();
    char *device_ptr = device.c_str();

    char errbuf[PCAP_ERRBUF_SIZE];

    // Call the function to fuzz
    struct pcap *pcap = pcap_open_live(device_ptr, snaplen, promisc, to_ms, errbuf);

    // Close the pcap structure if it was opened successfully
    if (pcap != NULL) {
        pcap_close(pcap);
    }

    return 0;
}