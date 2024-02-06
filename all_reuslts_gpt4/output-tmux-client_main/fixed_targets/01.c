#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "event2/event.h"

#define MAX_ARGS 10
#define MAX_ARG_LEN 20

extern "C" int client_main(struct event_base * base, int argc, char ** argv, size_t flags, int feat);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct event_base *base = event_base_new();
    assert(base != NULL);

    int argc = stream.ConsumeIntegralInRange<int>(0, MAX_ARGS);
    char **argv = new char*[argc+1];

    for (int i = 0; i < argc; i++) {
        std::string arg = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, MAX_ARG_LEN));
        argv[i] = strdup(arg.c_str());
    }
    argv[argc] = NULL;

    size_t flags = stream.ConsumeIntegral<size_t>();
    int feat = stream.ConsumeIntegral<int>();

    client_main(base, argc, argv, flags, feat);

    for (int i = 0; i < argc; i++) {
        free(argv[i]);
    }
    delete[] argv;

    event_base_free(base);

    return 0;
}