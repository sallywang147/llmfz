#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "zdict.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0;
    }

    FuzzedDataProvider stream(data, size);

    // Define and initialize parameters for ZDICT_trainFromBuffer_legacy
    size_t dictBufferCapacity = stream.ConsumeIntegral<size_t>();
    std::vector<char> dictBuffer(dictBufferCapacity);

    size_t samplesBufferCapacity = stream.ConsumeIntegral<size_t>();
    std::vector<char> samplesBuffer(samplesBufferCapacity);

    size_t* samplesSizes = stream.ConsumeIntegral<size_t*>();
    int nbSamples = stream.ConsumeIntegral<int>();

    ZDICT_legacy_params_t params;
    params.dictID = stream.ConsumeIntegral<unsigned>();
    params.compressionLevel = stream.ConsumeIntegral<int>();

    // Call ZDICT_trainFromBuffer_legacy
    ZDICT_trainFromBuffer_legacy(dictBuffer.data(), dictBufferCapacity, samplesBuffer.data(), &samplesSizes, nbSamples, &params);

    return 0;
}