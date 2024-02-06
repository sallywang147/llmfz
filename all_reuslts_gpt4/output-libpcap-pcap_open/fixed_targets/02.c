#include <pcap/pcap.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    const std::string source = stream.ConsumeRandomLengthString();
    int snaplen = stream.ConsumeIntegral<int>();
    int flags = stream.ConsumeIntegral<int>();
    int read_timeout = stream.ConsumeIntegral<int>();
    struct pcap_rmtauth auth;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Consume data for the auth struct
    auth.type = stream.ConsumeIntegral<int>();
    auth.username = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());
    auth.password = const_cast<char*>(stream.ConsumeRandomLengthString().c_str());

    struct pcap *pcap_handle = pcap_open(const_cast<char*>(source.c_str()), snaplen, flags, read_timeout, &auth, errbuf);

    if (pcap_handle != NULL) {
        pcap_close(pcap_handle);
    }

    return 0;
}