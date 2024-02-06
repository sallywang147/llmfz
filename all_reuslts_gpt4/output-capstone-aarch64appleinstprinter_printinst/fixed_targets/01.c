#include <capstone/capstone.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
    void AArch64AppleInstPrinter_printInst(struct MCInst * MI, size_t Address, char * Annot, struct SStream * O);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    struct MCInst MI;
    size_t Address = stream.ConsumeIntegral<size_t>();
    std::string Annot = stream.ConsumeRandomLengthString();
    struct SStream O;

    AArch64AppleInstPrinter_printInst(&MI, Address, const_cast<char*>(Annot.c_str()), &O);

    return 0;
}