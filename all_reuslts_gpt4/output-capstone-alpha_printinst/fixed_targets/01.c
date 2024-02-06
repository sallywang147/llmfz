#include <stdint.h>
#include <stddef.h>

#include <capstone/capstone.h>
#include <capstone/platform.h>

#include <fuzzer/FuzzedDataProvider.h>

struct MCInst {
    unsigned int opcode;
    unsigned int size;
    unsigned int address;
    unsigned int id;
};

struct SStream {
    char *buffer;
    size_t size;
    size_t index;
};

extern "C" void Alpha_printInst(struct MCInst * MI, struct SStream * O, char * Info);

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct MCInst MI;
    MI.opcode = stream.ConsumeIntegral<unsigned int>();
    MI.size = stream.ConsumeIntegral<unsigned int>();
    MI.address = stream.ConsumeIntegral<unsigned int>();
    MI.id = stream.ConsumeIntegral<unsigned int>();

    struct SStream O;
    std::vector<char> buffer = stream.ConsumeBytes<char>(stream.remaining_bytes() / 2);
    O.buffer = buffer.data();
    O.size = buffer.size();
    O.index = stream.ConsumeIntegralInRange<size_t>(0, O.size);

    std::string Info = stream.ConsumeRemainingBytesAsString();

    Alpha_printInst(&MI, &O, const_cast<char*>(Info.c_str()));

    return 0;
}