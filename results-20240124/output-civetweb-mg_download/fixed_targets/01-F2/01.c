#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "civetweb.h"

extern "C" {
  #include <algorithm>
  int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider stream(data, size);
    const std::string host = stream.ConsumeRandomLengthString();
    const int port = stream.ConsumeIntegral<int>();
    const int use_ssl = stream.ConsumeBool();
    const std::string ebuf = stream.ConsumeRandomLengthString();
    const size_t ebuf_len = stream.ConsumeIntegral<size_t>();
    const std::string fmt = stream.ConsumeRandomLengthString();

    mg_download(const_cast<char*>(host.c_str()), port, use_ssl,
                const_cast<char*>(ebuf.c_str()), ebuf_len,
                const_cast<char*>(fmt.c_str()));
    return 0;
  }
}