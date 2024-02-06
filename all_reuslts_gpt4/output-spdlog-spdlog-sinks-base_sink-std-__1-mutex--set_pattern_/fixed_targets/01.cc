#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <mutex>

#include "spdlog/sinks/base_sink.h"

class MySink : public spdlog::sinks::base_sink<std::mutex> {
protected:
    void sink_it_(const spdlog::details::log_msg& msg) override {
        // Do nothing
    }
    void flush_() override {
        // Do nothing
    }
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    std::string pattern = stream.ConsumeRandomLengthString();
    MySink sink;

    sink.set_pattern_( &sink, &pattern );

    return 0;
}