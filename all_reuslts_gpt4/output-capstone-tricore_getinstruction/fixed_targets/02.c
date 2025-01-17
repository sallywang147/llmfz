#include <fuzzer/FuzzedDataProvider.h>
#include <capstone/capstone.h>
#include <capstone/tricore.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    size_t handle = stream.ConsumeIntegral<size_t>();
    size_t ByteLen = stream.ConsumeIntegral<size_t>();
    size_t Address = stream.ConsumeIntegral<size_t>();
    std::string Bytes = stream.ConsumeBytesAsString(ByteLen);
    std::string Info = stream.ConsumeRandomLengthString();

    struct MCInst MI;
    short Size;

    TriCore_getInstruction(handle, Bytes.data(), ByteLen, &MI, &Size, Address, Info.data());

    return 0;
}