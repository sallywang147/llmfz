#include <fuzzer/FuzzedDataProvider.h>
#include <llvm/MC/MCInst.h>
#include <llvm/Support/raw_ostream.h>

extern "C" void Alpha_LLVM_printInstruction(struct MCInst * MI, struct SStream * O, char * Info);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    FuzzedDataProvider stream(data, size);

    llvm::MCInst MI;
    MI.setOpcode(stream.ConsumeIntegral<int>());

    // Consume up to 4 operands
    for (int i = 0; i < 4 && stream.remaining_bytes() > 0; ++i) {
        MI.addOperand(llvm::MCOperand::createImm(stream.ConsumeIntegral<int>()));
    }

    llvm::SmallVector<char, 256> Vec;
    llvm::raw_svector_ostream O(Vec);

    std::string Info = stream.ConsumeRemainingBytesAsString();

    Alpha_LLVM_printInstruction(&MI, &O, const_cast<char*>(Info.c_str()));

    return 0;
}