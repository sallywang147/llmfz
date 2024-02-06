#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <pcap/pcap.h>

extern "C" {
#include <pcap/pcap.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    pcap_init(0);
    initialized = true;
  }

  FuzzedDataProvider provider(data, size);
  // Generate a random device name.
  char device_name[16];
  provider.ConsumeBytes<char>(device_name, sizeof(device_name) - 1);
  device_name[sizeof(device_name) - 1] = '\0';

  // Generate a random snaplen.
  int snaplen = provider.ConsumeIntegralInRange<int>(0, 1 << 16);

  // Generate a random promisc flag.
  int promisc = provider.ConsumeBool();

  // Generate a random timeout.
  int timeout = provider.ConsumeIntegralInRange<int>(0, 1000);

  // Generate a random error buffer.
  char errbuf[PCAP_ERRBUF_SIZE];
  provider.ConsumeBytes<char>(errbuf, sizeof(errbuf) - 1);
  errbuf[sizeof(errbuf) - 1] = '\0';

  // Open the device.
  pcap_t* handle = pcap_open_live(device_name, snaplen, promisc, timeout, errbuf);
  if (handle == nullptr) {
    return 0;
  }

  // Close the device.
  pcap_close(handle);

  return 0;
}
```

The build issue is caused by the missing `extern "C" {}` around the `#include <pcap/pcap.h>` directive. This is necessary because the `pcap.h` header file contains C declarations, and the C++ compiler expects C++ declarations. By wrapping the `#include` directive with `extern "C" {}`, we tell the compiler to treat the declarations in the header file as C declarations, which resolves the build issue.